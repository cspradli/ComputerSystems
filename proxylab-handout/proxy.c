#include <stdio.h>
#include "csapp.h"
/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400
int parse_request(char *str, char *mathod, char* protocol, char *host_port, char *resource, char *version);
/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

int main(int argc, char *argv[])
{
    int listen;
    char* port = argv[1];
    listen = Open_listenfd(port);
    while (1)
    {
        /* code */
    }
    
    
    printf("%s", user_agent_hdr);
    return 0;
}
