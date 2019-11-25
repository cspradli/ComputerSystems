#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

// These two must be declared globally
struct addrinfo hints;
struct addrinfo *infoptr;

int main(int argc, char**argv){
    char *address_to_connect_to = "www.cs.unca.edu";
    int port_to_connect_to = 80;
    char *webpage_to_get = "/~drawert/cs335/";

    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("Error creating socket: ");
        exit(1);
    }

    // DNS lookup of IP address
    hints.ai_family = AF_INET;

    if( getaddrinfo( address_to_connect_to, NULL, &hints, &infoptr) != 0 ){
        perror("Error looking up DNS address: ");
        exit(1);
    }

    char ip_address[256];
    struct addrinfo *p;

    int connect_successful = 0;

    for( p = infoptr ; p != NULL ; p = p->ai_next){
        getnameinfo(p->ai_addr, p->ai_addrlen, ip_address, sizeof(ip_address), NULL, 0 , NI_NUMERICHOST);

        struct sockaddr_in serv_addr;
        memset(&serv_addr, '0', sizeof(serv_addr));  //zero out everything
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port_to_connect_to);

        if( inet_pton(AF_INET, ip_address, &serv_addr.sin_addr) <= 0){
            perror("Address translation error: ");
            exit(1);
        }
        printf("Trying to connect() to %s:%i\n", ip_address, port_to_connect_to);
        if( connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
            perror("Connection error, could not connect: ");
            continue; // Try the next IP address in the list
        }else{
            connect_successful = 1;
            break;
        }
    }
    freeaddrinfo(infoptr);  // clean up 

    if( ! connect_successful){
        printf("Not able to connect\n");
        exit(1);
    }

    // Send HTTP Request
    char request_buffer[1000];
    request_buffer[0] = '\0';

    strcat(request_buffer, "GET ");
    strcat(request_buffer, webpage_to_get);
    strcat(request_buffer, " HTTP/1.0\r\n");

    strcat(request_buffer, "Host: ");
    strcat(request_buffer, address_to_connect_to);
    strcat(request_buffer, "\r\n");

    strcat(request_buffer, "\r\n");  // Must end HTTP with blank line

    send(sockfd, request_buffer, strlen(request_buffer), 0);

    // Read HTTP Response
    int buffer_size = 1024;
    char *response_buffer = (char *) malloc(sizeof(char)*buffer_size);
    int bytes_read=0;
    int total_bytes_read = 0;
    
    while( (bytes_read = read(sockfd, &response_buffer[total_bytes_read], (buffer_size-total_bytes_read) ) ) > 0){
        total_bytes_read += bytes_read;
        if(total_bytes_read >= buffer_size-1){
            //realloc response buffer
            buffer_size += 1024;
            response_buffer = (char *) realloc(response_buffer,sizeof(char)*(buffer_size+1));
        }
    }


    printf("%s", request_buffer);
    printf("%s\n\n", response_buffer);

    free(response_buffer);

    return 0;
}




