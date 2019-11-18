/* $begin tinymain */
/*
 * tiny.c - A simple, iterative HTTP/1.0 Web server that uses the 
 *     GET method to serve static and dynamic content.
 */
#include "csapp.h"

typedef struct
{
    int port;
    char *host;
    char*path;
    char *protocol;
} http;

typedef struct{
    int port;
    char *host;
    char *path;
    char *protocol;
} request;

request *parse_uri(char *uri);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);
void build_http(char *uri, char *host, int port, char *path, rio_t *temp);
int parse_request(char *uri, char *hostname, char *path, int port);
void http_handle(int fd);

int main(int argc, char **argv) 
{
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    /* Check command line args */
    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(1);
    }

    listenfd = Open_listenfd(argv[1]);
    while (1) {
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); //line:netp:tiny:accept
    Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);
	http_handle(connfd);                                             //line:netp:tiny:doit
	Close(connfd);                                            //line:netp:tiny:close
    }
}
/* $end tinymain */

/*
 * doit - handle one HTTP request/response transaction
 */
/* $begin doit */
void http_handle(int fd) 
{
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char http_header[MAXLINE];
    char hostname[MAXLINE], path[MAXLINE];
    rio_t rio, serv;
    int end_server;
    int port;
    /* Read request line and headers */
    Rio_readinitb(&rio, fd);
    if (!Rio_readlineb(&rio, buf, MAXLINE))  //line:netp:doit:readrequest
        return;
    printf("%s", buf);
    sscanf(buf, "%s %s %s", method, uri, version);       //line:netp:doit:parserequest
    if (strcasecmp(method, "GET")) {                     //line:netp:doit:beginrequesterr
        clienterror(fd, method, "501", "Not Implemented",
                    "Tiny does not implement this method");
        return;
    }                                                    //line:netp:doit:endrequesterr                            //line:netp:doit:readrequesthdrs

    request *req = parse_uri(uri);
    build_http(uri, hostname, port, path, &rio);

}

/* $end read_requesthdrs */
void build_http(char *uri, char *host, int port, char *path, rio_t *temp){
    /**
     * TODO build the http header
     **/

    
}

request *parse_uri(char *uri){
    request *ret;
    char *past_prot;
    char *https = "https";
    ret = malloc(sizeof(request));
    if (ret == NULL) printf("malloc failed\n");

    char *in_url = malloc(strlen(uri)+1);
    strcpy(in_url, uri);

    if(strstr(uri, https)){
        printf("HTTPS protocol not implemented\n");
        past_prot = &in_url[8];
    } else {
        past_prot = &in_url[7];
    }

    printf("URI: %s\n", in_url);
    printf("ADDR: %s\n", past_prot);
    char* slash = strchr(past_prot, '/');
    char *path = malloc(strlen(in_url)+1);
    strcpy(path, slash);
    slash[0] = '\0';
    printf("HOST %s\n", past_prot);
    printf("PATH: %s\n", path);
    ret->protocol = "HTTP";
    ret->host = past_prot;
    ret->path = path;
    ret->port = 8080;
    return ret;
}

int parse_request(char *uri, char *hostname, char *path, int port){
    port = 8080;
    char port_c[64];
    char protocol[64];
    char host_port[256];
    printf("in parse\n");
    printf("ahh %s\n", uri);
    if(strstr(uri, "http://") == uri){
        printf("in parse 1\n");
        //sscanf(uri, "%[^:]", protocol);
        //printf("proto %s\n", protocol);
        sscanf(uri, "%[^:]//%[^/]%s", protocol, host_port, path);
        //printf("22 %s, %s, %s", protocol, host_port, path);
    } else {
        printf("in parse 2\n");
        sscanf(uri, "%[^/]%s", host_port, path);
        //printf("11 %s, %s", host_port, path);
    }
    //printf("%s\n", host_port);
    if(!strstr(host_port, ":")){
        //printf("in parse 3\n");
        sscanf(host_port, "%[^:]%s", hostname, port_c);
    }
    //printf("in parse 4\n");
    port = atoi(port_c);
    printf("protocol: %s\nhost: %s\npath: %s\nport: %d\n", protocol, host_port, path, port);
    return 1;
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
