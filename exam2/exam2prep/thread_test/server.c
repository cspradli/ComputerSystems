#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

void* server_proc(void *arg_in){
    int* client_fd = (int) *arg_in;
    int client_fd = *arg;
    free(arg_in);
    char buff = malloc(100);
    printf("I got another connection\n");
    for (int i=0;i<10;i++){
        sprinf(buff,"%i\n",i);
        send(client_fd,"Welcome %i", strlen(buff));
    }
    close(clientfd);
    free(buff);
}

int main(){
    
    int server_sock;
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if(server_sock < 0){
        perror("Error creating socket: ");
        exit(1);
    }

    struct sockaddr_in my_addr;
    memset(&my_addr, 0, sizeof(struct sock_addr_un));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons( 8888 );

    if (bind(server_sock, (struct sockaddr *)&my_addr, sizeof(my_addr) < 0)){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_sock, 3) < 0){
        perror("listen error");
        exit(EXIT_FAILURE);
    }

    while(1){
        int new_sock = accept(server_fd, 
                             (struct sockaddr *)&my_addr,
                             (socklen_t*)&my_addr);
        int tmp_fd = malloc(sizeof(int));
        tmp_fd = new_sock;
        pthread_create(NULL, NULL, server_proc, (void *) tmp_fd);
    }

