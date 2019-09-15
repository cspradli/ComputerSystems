/*
 * Directory function implementations for linked list implementation and sorting
 * Goes in conjunction with linked_list files
 * Author: Caleb Spradlin
 * Date: 09/15/19
 */
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "directory.h"

#define MAX_PATH 1024

void dir_put(char *path_name){
    linked_list *ll;
    char name[MAX_PATH];
    Dirent *dp;
    DIR *dirPointer;

    ll = create_linked_list();
}

void dir_print(linked_list *ll){
}
