/*
 * File input function implementations for linked list implementation and sorting
 * Goes in conjunction with linked_list files
 * Author: Caleb Spradlin
 * Date: 09/28/19
 */

#include "file_input.h"

void read_string(linked_list *ll, const char *file_name){
    FILE* in_file = fopen(file_name, "r");
    char s[2];
    fscanf(in_file, "%s", &s[0]);
    while (!feof(in_file)) {
        printf("%s ", s);
        linked_list_insertion(ll, s);
        fscanf(in_file, "%s", &s[0]);
    }
    printf("\n");
    fclose(in_file);
    
}
