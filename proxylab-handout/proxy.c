/*
 * proxy.c a simple proxy for CSAPP
 * Author: Caleb Spradlin
 * Date: 11.18.2019
 */
#include "csapp.h"

typedef struct{
    int port;
    char *host;
    char *path;
    char *protocol;
} request;

/* Function prototypes */
void read_requesthdrs(rio_t *rp);
request *parse_uri(char *uri);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);
void build_http(request *http_request, rio_t *temp);
int parse_request(char *uri, char *hostname, char *path, int port);
void http_handle(int fd);


int main(int argc, char **argv) {
    
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
    printf("======================================================\n");
	
    clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);
	http_handle(connfd);
	Close(connfd);

    printf("======================================================\n");
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
    read_requesthdrs(&rio);
    if (strcasecmp(method, "GET")) {                     //line:netp:doit:beginrequesterr
        clienterror(fd, method, "501", "Not Implemented",
                    "Tiny does not implement this method");
        return;
    }                                                    //line:netp:doit:endrequesterr                            //line:netp:doit:readrequesthdrs

    request *req = parse_uri(uri);
    build_http(req, &rio);

}

/* $end read_requesthdrs */
void build_http(request *in_request, rio_t *temp){
    /**
     * TODO build the http header
     **/

    
}

request *parse_uri(char *uri){
    char *past_prot;
    const char *http = "http://";
    const char *https = "https://";
    //const char *port_indicator = ":";
    request *ret;
    ret = malloc(sizeof(request));
    if (ret == NULL) printf("malloc failed\n");
    char *in_url = malloc(strlen(uri)+1);
    strcpy(in_url, uri);

    if(strstr(uri, http) == NULL && strstr(uri, https) == NULL){
        printf("No protocol indicated\n");
        past_prot = &in_url[0];
    }

    if(strstr(uri, https) == https){
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
    printf("PATH: %s\n\n", path);
    ret->protocol = "HTTP";
    ret->host = past_prot;
    ret->path = path;
    ret->port = 8080;
    return ret;
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
/* $begin read_requesthdrs */
void read_requesthdrs(rio_t *rp) 
{
    char buf[MAXLINE];

    Rio_readlineb(rp, buf, MAXLINE);
    printf("%s", buf);
    while(strcmp(buf, "\r\n")) {          //line:netp:readhdrs:checkterm
	Rio_readlineb(rp, buf, MAXLINE);
	printf("%s", buf);
    }
    return;
}
/* $end read_requesthdrs */

