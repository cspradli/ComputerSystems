/**
 * For proxy file
 * 11.11.2019
 * Caleb Spradlin
 * CSCI 335
 **/
#include <stdbool.h>

typedef struct{
    int port;
    char *host;
    char *path;
    char *protocol;
} request;


void http_handle(int connect_fd);

void build_http(char *uri, char *host, char *path, int *port);

int conn_end(char *host, int port, char *http);

request *parse_request(char *str);