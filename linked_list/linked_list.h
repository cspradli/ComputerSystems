/*
 * Linked list header file
 * For Systems II
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/*
 * This program implements a linked list
 */

typedef struct ELE {
	char* value;
	struct ELE *next;
} node;

/* Linked list structure */
typedef struct {
	node *head;
	node *tail;
	int size;
} linked_list;

/********** Operations on linked list **************/

/*
 * Create empy linked list
 */

linked_list *create_linked_list();

/*
 * Destroy linked list
 *
 * Returns true if succesfull
 * Returns false if ll is Null or otherwise unsuccesfull
 *
 */
bool linked_list_destroy(linked_list *ll);

/*
 *
 * Add to linked list
 * Returns true if succesfull
 * Returns false if ll is null or otherwise unsuccesfull
 */
bool linked_list_add(linked_list *ll, char* key);

/*
 * Delete element from linked list
 * Returns true if succesfull
 * Returns false if ll is null, empty, or otherwise unsuccesfull
 */
bool linked_list_delete(linked_list *ll, char* key);

/*
 * Search for element by key
 * Returns node with correct key
 */
node linked_list_search(linked_list *ll, char* key);

/*
 * Gets the node based on position
 * Returns the node
 * Reuturns 0 if unsuccesful
 */
node linked_list_get(linked_list *ll, int position);
