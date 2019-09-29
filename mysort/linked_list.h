/*
 * Linked list header file
 * For Systems II
 * Author: Caleb Spradlin
 * 09/03/2019
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/*
 * This program implements a linked list
 */

typedef struct ELE {
	int data;
	struct ELE *next;
} node;

/* Linked list structure */
typedef struct {
	node* head;
	int count;
} linked_list;

/********** Operations on linked list **************/

/*
 * Create empy linked list
 */

linked_list *create_linked_list();

/*
 * Destroy linked list
 * Takes in ll
 * Returns true if succesfull
 * Returns false if ll is Null or otherwise unsuccesfull
 *
 */
bool linked_list_destroy(linked_list *ll);

/*
 *
 * Add to linked list
 * Takes in ll and string(char array)
 * Returns true if succesfull
 * Returns false if ll is null or otherwise unsuccesfull
 */
bool linked_list_add(linked_list *ll, int input);


/*
 * Delete element from linked list
 * Takes in ll and node with which to compare
 * Returns true if succesfull
 * Returns false if ll is null, empty, or otherwise unsuccesfull
 */
bool linked_list_delete(linked_list *ll, node *key);

/*
 * Search for element by key
 * Takes ll and a string (char array)
 * Returns node with correct key
 */
node *linked_list_search(linked_list *ll, int input);

/*
 * Gets the node based on position
 * Takes linked_list and postion
 * Returns the node
 * Reuturns NULL if unsuccesful
 */
node *linked_list_get(linked_list *ll, int position);

/*
 * Prints out entire list
 * Takes in linked list
 */
void linked_list_print(linked_list *ll);
