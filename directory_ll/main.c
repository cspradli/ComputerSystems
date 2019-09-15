/*
 * Main program for directory printing
 * Goes in conjunction with directory and linked_list files
 * Author: Caleb Spradlin
 * Date: 09/15/19
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    char cwd[PATH_MAX];
    if (argc > 1) {
        printf("Printing directory of: %s\n", argv[1]);
        return dir_print(argv[1]) ;
    } else {
        if (getcwd(cwd, sizeof(cwd)) != NULL){
            printf("Printing current directory %s\n", cwd);
            return dir_print(cwd);
        } else {
            printf("Error occured\n");
            return 0;
        }
    }
}