//Linked list C file

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "linked_list.h"

linked_list *create_linked_list(){
    linked_list *ll = malloc(sizeof(linked_list));
    if(ll == NULL){return NULL;}
    ll->count = 0;
    ll->head = NULL;
    printf("Linked list created\n");
    return ll;
}

bool linked_list_destroy(linked_list *ll){
    if (ll != NULL){
        node *current = ll->head;
        node *next;
        while (current != NULL){
            next = current->next;
            free(current);
            current = next;
        }
        ll->head = NULL;
        free(ll);
	printf("Linked list destroyed\n");
        return true;
    }
    return false;
}

bool linked_list_add(linked_list *ll, char key[100]){
    node *newn;
    newn = malloc(sizeof(node));
    if (ll == NULL){
        free(newn);
        return false;
    }
    if (newn == NULL){ return false; }

    newn->data = key;
    newn->next = ll->head;
    ll->head = newn;
    ll->count++;
    printf("Linked list added with key: %s\n", newn->data);
    return true;
}

bool linked_list_delete(linked_list *ll, node *key){
    if (ll == NULL || ll->count == 0){ 
	    printf("Unable to delete\n");
	    return false; }
    node *tempToFree = NULL;
    node *previous = NULL;
    tempToFree = ll->head;
    if (tempToFree != NULL && tempToFree->data == key->data){
	printf("Deleted head moved on\n");
        ll->head = ll->head->next;
        free(tempToFree);
        ll->count--;
        return true;
    }

    while (tempToFree != NULL && tempToFree->data != key->data){
        previous = tempToFree;
        tempToFree = tempToFree->next;
        if (tempToFree->data == key->data){
            previous->next = tempToFree->next;
            free(tempToFree);
            ll->count--;
	    printf("Found it!\n");
            return true;
        }
	printf("Still looking\n");
    }

    if(tempToFree == NULL) { return false;}
    previous->next = tempToFree->next;
    printf("Freeing everything\n");
    free(tempToFree);
    free(previous);
    return false;
    
}

node *linked_list_get(linked_list *ll, int position){
    node *tempToFree = ll->head;
    printf("Temptofree node key is %s\n", tempToFree->data);
    int counter = 0;
    if (ll == NULL || ll->count == 0){ return tempToFree; }
    while(tempToFree != NULL){
        if (counter == position){
	    printf("found the item\n");
            return tempToFree;
        }
        tempToFree = tempToFree->next;
        counter++;
    }
    return tempToFree;
}

node *linked_list_search(linked_list *ll, char key[100]){
    node *tempToFree = NULL;
    if (ll == NULL || ll->count == 0){ return tempToFree; }
    tempToFree = ll->head;
    while (tempToFree != NULL){
        if(tempToFree->data == key){
            return tempToFree;
        }
        tempToFree = tempToFree->next;
    }
    return tempToFree;
}
