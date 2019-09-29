/*
 * Directory function implementations for linked list implementation and sorting
 * Goes in conjunction with linked_list files
 * Author: Caleb Spradlin
 * Date: 09/15/19
 */

#include <dirent.h> 
#include <sys/types.h> 
#include <sys/param.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <string.h> 
#include <errno.h>
#include <ctype.h>
#include "directory.h"

#define MAX_PATH 1024

void dir_put(char *path_name){
    linked_list *ll;
    struct dirent *dir;
    char name[MAX_PATH];
    DIR *dirPointer;

    ll = create_linked_list();

    if ((dirPointer = opendir(path_name)) == NULL){
        printf("Can't open %s\n", path_name);
        return;
    }
    while ((dir = readdir(dirPointer)) != NULL){
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) continue;
        dir->d_name[0] = tolower(dir->d_name[0]);
        sprintf(name, "%s/%s", path_name, dir->d_name);
        linked_list_insertion(ll, dir->d_name);
    }
    printf("LINKED LIST: ");
    linked_list_print(ll);
    closedir(dirPointer);
}
