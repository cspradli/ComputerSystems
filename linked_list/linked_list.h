/*
 * Linked list header file
 * For Systems II
 */

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
 * Returns true if succesfulle
 * Returns false if ll is Null or otherwise unsuccesfull
 *
 */
bool linked_list_destroy(linked_list *ll);
