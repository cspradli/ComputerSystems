/*
 * File input function implementations for linked list implementation and sorting
 * Goes in conjunction with linked_list files
 * Author: Caleb Spradlin
 * Date: 09/28/19
 */

#include "file_input.h"

void read_ints(linked_list *ll, const char *file_name){
    FILE* in_file = fopen(file_name, "r");
    int i = 0;
    fscanf(in_file, "%d", &i);
    while (!feof(in_file)) {
        printf("%d ", i);
        linked_list_insertion(ll, i);
        fscanf(in_file, "%d", &i);
    }
    printf("\n");
    fclose(in_file);
    
}
