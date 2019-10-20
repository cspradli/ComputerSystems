#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

// Function to manipulate the linked list

linked_list* linkedlist_initialize(){
	linked_list*ll = (linked_list*) malloc(sizeof(linked_list));
	ll->head = NULL;
	ll->end = NULL;
	ll->count = 0;
	return ll;
}

void linkedlist_destory(linked_list*ll){
	while(ll->head != NULL)
		linkedlist_delete(ll,ll->head);
	free(ll);	
}


int mystrcmp(char*a, char*b){
	if(strlen(a) > strlen(b)) return 1;
	if(strlen(a) < strlen(b)) return -1;
	return strcmp(a,b);
}

void linkedlist_add__insert_sort(linked_list*ll, char*data_in){
	//printf("linkedlist_add__insert_sort(%s)\n",data_in);
	node * n = (node*) malloc(sizeof(node));
	n->next = NULL;
	n->data = (char*) malloc( strlen(data_in)+1 );
	strcpy(n->data,data_in);

	node * current_node;
	node * prev_node;
	int inserted = 0;

	if(ll->head == NULL){
		//printf("\t empty list, put at HEAD\n");
		ll->head = n;
		ll->end = n;
	}else if (ll->head->next == NULL){  // there is only 1 node in the list
		if( mystrcmp( ll->head->data, n->data) > 0) {
			//printf("\t size 1 list, put at HEAD\n");
			n->next = ll->head;
			ll->head = n;
			ll->end = n->next;  //redundant, but nice for documentation
		}else{
			//printf("\t size 1 list, put at end\n");
			ll->head->next = n;
			ll->end = n; 
		}
	}else{
		//printf("\t size >1 list, iterating through\n");
		current_node = ll->head;
		prev_node = ll->head;
		//printf("\t checking first node of the list node(%s)\n",ll->head->data);
		if(mystrcmp( current_node->data , n->data ) > 0){
			//printf("\t inserting at HEAD\n");
			n->next = ll->head;
			ll->head = n;
		}else{
			while(current_node->next != NULL){
				current_node = current_node->next;
				//printf("\t comparing node(%s) with data\n",current_node->data);
				if( mystrcmp( current_node->data , n->data ) > 0){
					//printf("\t inserting before node(%s) after node(%s)\n",current_node->data, prev_node->data);
					prev_node->next = n;
					n->next = current_node;
					inserted = 1;
					break;
				}
				prev_node = prev_node->next;
			}
			if( ! inserted ){  // added to end of the list
				//printf("\tadding to the end of the list\n");
				current_node->next = n;
				ll->end = n;
			}
		}
		
	}
	ll->count++;
}


void linkedlist_add(linked_list*ll, char*data_in){
	node * n = (node*) malloc(sizeof(node));
	n->next = NULL;
	n->data = (char*) malloc( strlen(data_in)+1 );
	strcpy(n->data,data_in);
	if(ll->head == NULL){
		ll->head = n;
		ll->end = n;
	}else{
		ll->end->next = n;
		ll->end = n;
	}
	ll->count++;
}

void linkedlist_delete(linked_list*ll, node*to_delete){
	node * prev_node;
	if(ll->head == NULL){
		printf("Error, linkedlist_delete(): empty list\n");
		return;
	}
	if(to_delete == ll->head){
		ll->head = ll->head->next;
	}else{
		for(prev_node=ll->head;prev_node->next!=NULL;prev_node = prev_node->next){
			if(prev_node->next == to_delete)
				break;
		}
		if(prev_node->next == NULL){
			printf("Error, linkedlist_delete(): could not find element in list\n");
			return;
		}
		prev_node->next = to_delete->next;
	}
	ll->count--;
	free(to_delete->data);
	free(to_delete);
}

node* linkedlist_search(linked_list*ll, char*search_string){
	node *n;
	for(n=ll->head;n!=NULL;n = n->next){
		if( strcmp(n->data, search_string) == 0 )
			break;
	}
	if(n == NULL){
		printf("Error, linkedlist_search(): could not find element in list\n");
		return NULL;
	}
	return n;
}

node* linkedlist_get(linked_list*ll, int position){
	int count = 0;
	node * n = ll->head;
	if(ll->head == NULL){
		printf("Error, linkedlist_get(): empty list\n");
		return NULL;
	}
	while(count < position){
		if(n->next == NULL){
			printf("Error, linkedlist_get(): list shorter than %i\n",position);
			return NULL;
		}
		n = n->next;
		count++;
	}
	return n;
}
