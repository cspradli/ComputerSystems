#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    char *in_url_temp = "http://www.cs.unca.edu/~drawert/cs335/";
    char *in_url = malloc(strlen(in_url_temp)+1);
    strcpy(in_url, in_url_temp);

    char *str2 = &in_url[7];

    printf("in_url %s\n", in_url);
    printf("str2 %s\n", str2);

    char* slash = strchr(str2, '/');

    printf("%s\n", slash);

    char *path = malloc(strlen(in_url)+1);
    strcpy(path, slash);

    slash[0] = '\0';
    printf("str2 %s\n", str2);
    printf("path %s\n", path);
    return 0;
}
