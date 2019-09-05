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
    return true;
}

bool linked_list_delete(linked_list *ll, node *key){
    if (ll == NULL || ll->count == 0){ return false; }
    node *tempToFree = NULL;
    node *previous = NULL;
    tempToFree = ll->head;
    if (tempToFree != NULL && tempToFree->data == key->data){
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
            return true;
        }
    }

    if(tempToFree == NULL) { return false;}
    previous->next = tempToFree->next;
    free(tempToFree);
    free(previous);
    return false;
    
}

node *linked_list_get(linked_list *ll, int position){
    node *tempToFree = ll->head;
    if (tempToFree == NULL){return tempToFree;}
    int counter = 0;
    while(tempToFree != NULL){
        if (counter == position){ return tempToFree; }
        counter++;
        tempToFree = tempToFree->next;
    }
}

node *linked_list_search(linked_list *ll, char key[100]){
    node *current = NULL;
    if (ll == NULL || ll->count == 0){ return current; }
    current = ll->head;
    while (current != NULL){
        if(current->data == key){
            return current;
        }
        current = current->next;
    }
    return current;
}

void printList(linked_list *ll){ 
    node *current = ll->head;
    while (current != NULL){ 
     printf(" %s ", current->data); 
     current = current->next; 
  } 
} 
