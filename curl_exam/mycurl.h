#ifndef mycurl_h
#define mycurl_h

#include <pthread.h>


char* parse_and_fetch_url(char*url);


char* mycurl(char *address_to_connect_to, int port_to_connect_to, char *webpage_to_get);

#endif /* mycurl_h */
