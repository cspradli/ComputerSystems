/*
 * proxy.c a simple proxy for CSAPP
 * Author: Caleb Spradlin
 * Date: 11.20.2019
 */

/**
 * NOTE! ATTENTION! This is what I currently have. It is having trouble with
 * loading images but has all concurrency and basic proxy needs. 
 * I am working on the chached version now and will have it ready ASAP
 **/
#include <stdio.h>
#include <pthread.h>
#include "csapp.h"
#include "linked_list.h"

#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 409600
typedef struct{
    int port;
    char host[256];
    char path[1024];
    char protocol[24];
} request;

/* Function prototypes */
void read_requesthdrs(rio_t *rp);
request *parse_uri(char *uri);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);
void build_http(char *header, request *http_request, rio_t *temp);
int parse_request(char *uri, char *hostname, char *path, int port);
void http_handle(int fd);
int endserv_connect(request *req, char *http_head);
void *thread(void *vargp);
//request *parse_again(char *uri);

static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";
static const char *conn_hdr = "Connection: close\r\n";
static const char *prox_hdr = "Proxy-Connection: close\r\n";

int main(int argc, char **argv) {
    
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    linked_list *ll;
    ll = create_linked_list();
    pthread_t tid;
    /* Check command line args */
    if (argc != 2) {
	    fprintf(stderr, "usage: %s <port>\n", argv[0]);
	    exit(1);
    }
    linked_list_add(ll, "Yees");
    linked_list_print(ll);
    listenfd = Open_listenfd(argv[1]);
    while (1) {
    printf("======================================================\n");
	
    clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
    printf("Accepted connection from (%s, %s)\n", hostname, port);
    Pthread_create(&tid, NULL, thread, (void *) connfd);
	printf("TID %ld", tid);
    /*http_handle(connfd);
	Close(connfd);
    */
    }
}


/*
 * handle_http - handle one HTTP request/response transaction
 */
/* $begin http_handle */
void http_handle(int fd) 
{
    //struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char http_header[MAXLINE];
    //char hostname[MAXLINE], path[MAXLINE];
    rio_t rio, serv;
    int end_server;
    //int port;
    /* Read request line and headers */
    Rio_readinitb(&rio, fd);
    if (!Rio_readlineb(&rio, buf, MAXLINE))  //line:netp:doit:readrequest
        return;
    printf("%s", buf);
    sscanf(buf, "%s %s %s", method, uri, version);       //line:netp:doit:parserequest
    read_requesthdrs(&rio);
    if (strcasecmp(method, "GET")) {                     //line:netp:doit:beginrequesterr
        clienterror(fd, method, "501", "Not Implemented",
                    "Proxy does not implement other than GET");
        return;
    }                                                    //line:netp:doit:endrequesterr                            //line:netp:doit:readrequesthdrs
    request *req = parse_uri(uri);
    //request *req = parse_uri(uri);
    build_http(http_header, req, &rio);
    printf("From handle %s", http_header);
    end_server = endserv_connect(req, http_header);
    
    if (end_server < 0){
        printf("Connection failed \n");
        return;
    }
    
    printf("Connection succesful\n");
    Rio_readinitb(&serv, end_server);
    Rio_writen(end_server, http_header, strlen(http_header));
    size_t n;
    while ((n = Rio_readlineb(&serv, buf, MAXLINE))!=0)
    {
        //printf("PROXY: recieved %ld bytes.\n", n);
        printf("%s", buf);
        Rio_writen(fd, buf, n);
    }
    Close(end_server);
}


void build_http(char *http_header, request *in_request, rio_t *temp){
    //memset(http_header, 0, sizeof(http_header));
    strcat(http_header, "GET ");
    strcat(http_header, in_request->path);
    strcat(http_header, " HTTP/1.0\r\n");
    strcat(http_header, "Host: ");
    strcat(http_header, in_request->host);
    strcat(http_header, "\r\n");
    strcat(http_header, conn_hdr);
    strcat(http_header, prox_hdr);
    strcat(http_header, user_agent_hdr);
    strcat(http_header, "\r\n");
    printf("%s\n", http_header);
    
}

request *parse_uri(char *url){
    request *ret;
    ret = malloc(sizeof(request));
    if (ret == NULL) printf("malloc failed\n");

    char host[256] = "";
    int port = 80;
    char uri2[512] = "";
    char uri[512] = "/";
    int succ_parsing = 0;

    if (sscanf(url, "http://%99[^:]:%i/%199[^\n]", host, &port, uri2) == 3){ succ_parsing = 1; }
    else if (sscanf(url, "http://%99[^/]/%199[^\n]", host, uri2) == 2){ succ_parsing = 1; }
    else if (sscanf(url, "http://%99[^:]:%i[^\n]", host, &port) == 2) { succ_parsing = 1; }
    else if (sscanf(url, "http://%99[^\n]", host) == 1) { succ_parsing = 1; }
    strcat(uri, uri2);
    
    //ret->host = host;
    strcpy(ret->host, host);
    //ret->path = uri;
    strcpy(ret->path, uri);
    ret->port = port;
    //ret->protocol = "HTTP";
    strcpy(ret->protocol, "HTTP");
    printf("PARSE\nHOST %s\n", ret->host);
    printf("PORT: %d\n", ret->port);
    printf("URI %s\n", ret->path);
    printf("SUCCESS: %d\n\n", succ_parsing);
    return ret;

}

int endserv_connect(request *req, char *http_header){
    char portString[10];
    sprintf(portString, "%d", req->port);
    printf("Attempting connection to host '%s' through port '%s'\n", req->host, portString);
    return Open_clientfd(req->host, portString);
}


void *thread(void *vargp){
    int connfd = (int) vargp;
    printf("<<<<<<<<<<<<<<<<<<< Thread created connection = %d >>>>>>>>>>>>>>>>>>\n", connfd);
    Pthread_detach(pthread_self());
    http_handle(connfd);
    Close(connfd);
    printf("======================================================\n");
    //return NULL;
}
/* $begin clienterror */
void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg) 
{
    char buf[MAXLINE], body[MAXBUF];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}
/* $end clienterror */

/*
 * read_requesthdrs - read HTTP request headers
 */
void read_requesthdrs(rio_t *rp) 
{
    char buf[MAXLINE];

    Rio_readlineb(rp, buf, MAXLINE);
    printf("%s", buf);
    while(strcmp(buf, "\r\n")) {
	    Rio_readlineb(rp, buf, MAXLINE);
	    printf("%s", buf);
    }
    return;
}


