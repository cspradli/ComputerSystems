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

void read_file(int cap, const char* file_name, char *word, linked_list *ll);
/*
 * Puts the strings into a linked list via insertion add
 * Takes char *file_name as input
 * Returns nothing
 */
