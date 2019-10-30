/*
 * File functions discriptions for linked list implementation and sorting
 * Goes in conjunction with linked_list files
 * Author: Caleb Spradlin
 * Date: 09/28/19
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"


/* 
 * Reads in each file listed line by line and searches for the keyword. If it is present, bump up the counters.
 * Parameters cap to check capitolization, file_name of the file to look through, the key search word,
 * linked list to add the filename and how many times
 * Returns nothing
 */

void read_file(int cap, const char* file_name, char *word, linked_list *ll);
