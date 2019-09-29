/*
 * File input function implementations for linked list implementation and sorting
 * Goes in conjunction with linked_list files
 * Author: Caleb Spradlin
 * Date: 09/28/19
 */

#include <sys/types.h> 
#include <sys/param.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <string.h> 
#include <errno.h>
#include <ctype.h>
#include "file_input.h"

void read_ints(linked_list *ll, const char *file_name){
    FILE* in_file = fopen(file_name, "r");
    int i = 0;
    fscanf(in_file, "%d", &i);
    while (!feof(in_file)) {
        printf("%d ", i);
        linked_list_add(ll, i);
        fscanf(in_file, "%d", &i);
    }
    printf("\n");
    fclose(in_file);
    
}
