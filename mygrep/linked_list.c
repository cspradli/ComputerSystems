/*
 * Linked list c file for C programming lab
 * Author: Caleb Spradlin
 * Date: 9/16/19
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "linked_list.h"

linked_list *create_linked_list(){
    printf("Link list created\n");
    linked_list *ll = malloc(sizeof(linked_list));
    if(ll == NULL) return NULL;
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
	        free(current->data);
            free(current);
            current = next;
        }

        ll->head = NULL;
        free(ll);
        return true;
    }
    return false;
}

bool linked_list_add(linked_list *ll, char *key){
    node *newn;
    newn = malloc(sizeof(node));
   
    if (ll == NULL){
        free(newn);
        return false;
    }

    if (newn == NULL) return false;
    newn->data = key;
    newn->next = ll->head;
    ll->head = newn;
    ll->count++;
    return true;
}


bool linked_list_delete(linked_list *ll, node *key){
    if (ll == NULL || ll->count == 0) return false;
    node *tempToFree = NULL;
    node *previous = NULL;
    tempToFree = ll->head;

    //checks the head for compatability
    if (tempToFree != NULL && strcmp(tempToFree->data, key->data)==0){
        ll->head = ll->head->next;
	    free(tempToFree->data);
        free(tempToFree);
        ll->count--;
        return true;
    }
    
    while (tempToFree != NULL && strcmp(tempToFree->data, key->data) != 0){
        previous = tempToFree;
        tempToFree = tempToFree->next;

        if (strcmp(tempToFree->data, key->data) == 0){
            previous->next = tempToFree->next;
            free(tempToFree);
            ll->count--;
            return true;
        }

    }

    if(tempToFree == NULL)  return false;
    previous->next = tempToFree->next;
    free(tempToFree->data);
    free(previous->data);
    free(tempToFree);
    free(previous);
    return false;
    
}

node *linked_list_get(linked_list *ll, int position){
    node *current = ll->head;
    if (current == NULL) return current;
    int counter = 0;

    while(current != NULL){
        if (counter == position) return current;
        counter++;
        current = current->next;
    }

    printf("Node not found\n");
    return current=NULL;
}

node *linked_list_search(linked_list *ll, char *key){
    node *current = NULL;
    if (ll == NULL || ll->count == 0){ return current; }
    current = ll->head;

    while (current != NULL){
        if(strcmp(current->data, key) == 0){
            return current;
        }
        current = current->next;
    }

    return current;
}

void linked_list_print(linked_list *ll){ 
    node *current = ll->head;

    while (current != NULL){ 
     printf("%s ", current->data); 
     current = current->next; 
    }

    printf("\n"); 
} 

