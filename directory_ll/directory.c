/*
 * Directory function implementations for linked list implementation and sorting
 * Goes in conjunction with linked_list files
 * Author: Caleb Spradlin
 * Date: 09/15/19
 */
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int dir_print(char *);

int dir_print(char *path_name){
    char largeFileBuffer[8192];
    DIR *dirPointer = opendir(path_name);;
    if (dirPointer != NULL){
        
    }
}