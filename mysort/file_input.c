/*
 * File input function implementations for linked list implementation and sorting
 * Goes in conjunction with linked_list files
 * Author: Caleb Spradlin
 * Date: 09/28/19
 */

#include "file_input.h"

void read_ints(linked_list *ll, const char *file_name){
    FILE* in_file = fopen(file_name, "r");
    char *i = " ";
    fscanf(in_file, "%s", i);
    while (!feof(in_file)) {
        printf("%s ", i);
        linked_list_insertion(ll, i);
        fscanf(in_file, "%s", i);
    }
    printf("\n");
    fclose(in_file);
    
}
