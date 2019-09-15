/*
 * Directory function discriptions for linked list implementation and sorting
 * Goes in conjunction with linked_list files
 * Author: Caleb Spradlin
 * Date: 09/15/19
 */
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/*
 * Puts the contents/names inside the current durectory given by path into a ll structure
 * Takes char *path as input
 * Returns nothing
 */
void dir_put(char *path);

/*
 * Takes the linked list of directory names and prints them out (ll should already be sorted)
 * Takes linked list as inp
 * Returns nothing
 */
void dir_print(linked_list *ll);