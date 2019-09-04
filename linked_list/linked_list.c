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
    ll->tail = NULL;
    return ll;
}

linked_list_destroy(linked_list *ll){
    if (ll != NULL){
        while (ll->count > 0){ linked_list_delete(ll, " "); }
        free(ll);
    }
}

linked_list_add(linked_list *ll, char key[100]){
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
    if (ll->count == 0) { ll->tail = newn; }
    ll->count++;
    return true;
}

linked_list_delete(linked_list *ll, char key[100]){
    if (ll == NULL || ll->count == 0){ return false; }
    node *tempToFree = NULL;
    node *previous = NULL;
    tempToFree = ll->head;
    if (tempToFree != NULL && tempToFree->data == key){
        ll->head = ll->head->next;
        free(tempToFree);
        return true;
    }

    while (tempToFree != NULL && tempToFree->data != key){
        previous = tempToFree;
        tempToFree = tempToFree->next;
        if (tempToFree->data == key){
            previous->next = tempToFree->next;
            free(tempToFree);
            return true;
        }
    }

    if(tempToFree == NULL) { return false;}
    previous->next = tempToFree->next;
    free(tempToFree);
    free(previous);
    return false;
    
}