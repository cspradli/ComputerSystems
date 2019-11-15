#include <stdio.h>
#include "csapp.h"
#include <stdbool.h>
/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/**
 * Struct so the parser can return multiple different strings
 */
typedef struct{
    int port;
    char *host;
    char *path;
    char *protocol;
} request;

/*
 * Handles the http client transaction
 */
void http_handle(int connect_fd);

/**
 * Builds the http header from parsed request
 */
void build_http(char *uri, char *host, int port, char *path, rio_t *temp);

/**
 * Connect to the end server the client is attempting to reach
 */
int conn_end(char *host, int port, char *http);

/**
 * Parse the request with the given string
 */
request *parse_request(char *str);


/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

int main(int argc, char *argv[])
{
    int listen, conn;
    socklen_t client_len;
    char *host = NULL;
    char* port = argv[1];
    struct sockaddr_storage client_addr;

    listen = Open_listenfd(port);


    while (1)
    {
        client_len = sizeof(client_addr);
        conn = Accept(listen, (SA *)&client_addr, &client_len);
        Getnameinfo((SA*)&client_addr, client_len, host, MAXLINE, port, MAXLINE, AF_INET);
        printf("Got connection from %s %s\n", host, port);
        http_handle(conn);
        Close(conn);
    }
    
    
    printf("%s", user_agent_hdr);
    return 0;
}

void http_handle(int connect_fd){
    /**
     * TODO handle the http
     **/
    char *buffer = NULL, *method = NULL, *end_head = NULL, *path = NULL;
    int endserver;
    rio_t temp, serv;
    Rio_readinitb(&temp, connect_fd);
    Rio_readlineb(&temp, buffer, MAXLINE);
    request *parse = parse_request(buffer);
    if(strstr(parse->protocol, "GET")){
        printf("Protocol other than GET was used");
        return;
    }
    build_http(end_head, parse->host, parse->port, path, &temp);
    endserver = conn_end(parse->host, parse->port, method);
    if (endserver < 0) printf("Error in endserver\n");
    Rio_readinitb(&serv, endserver);
    Rio_writen(endserver,end_head, strlen(end_head));
    size_t message_size;
    while ((message_size = Rio_readlineb(&serv, buffer, MAXLINE)) !=0)
    {
        Rio_writen(connect_fd, buffer, message_size);
    }
    Close(connect_fd);
}

void build_http(char *uri, char *host, int port, char *path, rio_t *temp){
    /**
     * TODO build the http header
     **/

    
}

int conn_end(char *host, int port, char *http){
    char *port_s = NULL;
    sprintf(port_s, "%d", port);
    int ret = Open_clientfd(host, port_s);
    return ret;
}

request *parse_request(char *str){
    int port = 80;
    char *port_c = NULL;
    char *host = NULL;
    char *method = NULL, *url = NULL, *version = NULL, *protocol = NULL, *host_port = NULL, *path = NULL;
    request *new_req;

    new_req = malloc(sizeof(request));
    if (new_req == NULL){
        printf("Error for malloc\n");
    }

    sscanf(str, "%s %s %s", method, url, version);
    if(!strstr(url, "://")){
        sscanf(url, "%[^:]//%[^/]%s", protocol, host_port, path);
    } else {
        sscanf(url, "%[^/]%s", host_port, path);
    }

    if(strstr(host_port, ":")){
        sscanf(host_port, "%[^:]%s", host, port_c);
    } else {
        sprintf(port_c, "%d", port);
    }
    new_req->protocol = protocol;
    new_req->host = host;
    new_req->port = atoi(port_c);
    new_req->path = path;
    
    return new_req;
}
