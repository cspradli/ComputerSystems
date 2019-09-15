#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    char cwd[PATH_MAX];
    if (argc > 1) {
        return dir_print(argv[1]) ;
    } else {
        return dir_print()
        return 235 ;
    }
}