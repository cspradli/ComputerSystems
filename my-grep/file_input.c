/*
 * File input function implementations for linked list implementation and sorting
 * Goes in conjunction with linked_list files
 * Author: Caleb Spradlin
 * Date: 09/28/19
 */

#include "file_input.h"


void read_file(int cap, const char *file_name, linked_list *ll){
    
}
void read_string(linked_list *ll, const char *file_name){
    FILE* in_file = fopen(file_name, "r");
    char buffer[100];
    int len;
    //fscanf(in_file, "%s", &s[0]);
    if (in_file){
        while(fgets(buffer, 100, in_file)){
            len = strlen(buffer);
            if (buffer[len-1] == '\n') buffer[len-1] = '\0';

        }
    }
    while (!feof(in_file)) {
        //printf("%s ", s);
        //linked_list_insertion(ll, s);
        //fscanf(in_file, "%s", &s[0]);
    }
    printf("\n");
    fclose(in_file);
    
}
