/*
 * File input function implementations for linked list implementation and sorting
 * Goes in conjunction with linked_list files
 * Author: Caleb Spradlin
 * Date: 09/28/19
 */

#include "file_input.h"
#define MAX_LINE 1024

void read_file(int cap, const char *file_name, char *search, linked_list *ll){
    FILE *in_file = fopen(file_name, "r");
    char *line = NULL;
    int line_found = 0;
    int word_found = 0;
    size_t len = 0;
    ssize_t read;
    if (in_file){
        while ((read = getline(&line, &len, in_file)) != -1)
        {
            if (cap == 0){
                if (strstr(line, search) != NULL){
                    printf("Found no case\n");
                    line_found++;
                    word_found++;
                }
            }
            else if (cap == 1){
                if (strcasestr(line,search) != NULL){
                    printf("found case\n");
                    line_found++;
                    word_found++;
                }
            }
        }

        if (line_found > 0){
            //char *result = strcat(file_name, )
            char *result;
            sprintf(result, "%s: %d", file_name, word_found);
            printf(" Whats going in the linked list: %s\n", result);
            linked_list_insertion(ll, result);
        }
        
    }
    printf("\n");
    fclose(in_file);
}