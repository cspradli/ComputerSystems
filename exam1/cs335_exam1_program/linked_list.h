#ifndef linked_list_h
#define linked_list_h


// Define node of a linked list
struct node_t {
	char*data;
	struct node_t*next;
};
typedef struct node_t node;

// Define whole linked list "object"
typedef struct {
	node*head;
	node*end;
	int count;
} linked_list;


// Function to manipulate the linked list

linked_list* linkedlist_initialize();

void linkedlist_destory(linked_list*ll);

void linkedlist_add(linked_list*ll, char*data_in);

void linkedlist_add__insert_sort(linked_list*ll, char*data_in);

void linkedlist_delete(linked_list*ll, node*to_delete);

node* linkedlist_search(linked_list*ll, char*search_string);

node* linkedlist_get(linked_list*ll, int position);

#endif
