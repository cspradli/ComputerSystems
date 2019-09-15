/*
 * Main program for directory printing
 * Goes in conjunction with directory and linked_list files
 * Author: Caleb Spradlin
 * Date: 09/15/19
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "directory.h"

#define MAX_PATH 1024

int main(int argc, char *argv[]) {

    char cwd[MAX_PATH];
    if (argc > 1) {
        printf("Printing directory of: %s\n", argv[1]);
        dir_put(argv[1]) ;
    } else {
        if (getcwd(cwd, sizeof(cwd)) != NULL){
            printf("Printing current directory %s\n", cwd);
            dir_put(cwd);
        } else {
            printf("Error occured\n");
            return 0;
        }
    }
}