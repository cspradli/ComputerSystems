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
            free(current);
            current = next;
        }

        ll->head = NULL;
        free(ll);
        return true;
    }
    return false;
}

bool linked_list_add(linked_list *ll, int key){
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
    if (tempToFree != NULL && (tempToFree->data == key->data)){
        ll->head = ll->head->next;
        free(tempToFree);
        ll->count--;
        return true;
    }
    
    while (tempToFree != NULL && (tempToFree->data != key->data)){
        previous = tempToFree;
        tempToFree = tempToFree->next;

        if (tempToFree->data == key->data){
            previous->next = tempToFree->next;
            free(tempToFree);
            ll->count--;
            return true;
        }

    }

    if(tempToFree == NULL)  return false;
    previous->next = tempToFree->next;
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

node *linked_list_search(linked_list *ll, int key){
    node *current = NULL;
    if (ll == NULL || ll->count == 0) return current;
    current = ll->head;
    while (current != NULL){
        if(current->data == key) return current;
        current = current->next;
    }
    return current;
}

int compare_to(int i, int k){
    return i-k;
}

bool linked_list_insertion(linked_list *ll, int key){
    node *newn;
    newn = malloc(sizeof(node));

    if (ll == NULL) free(newn);
    if (newn == NULL) return false;
    //malloc needed memory for string
    newn->data = key;

    if (ll->head == NULL){
        ll->head = newn;
        ll->count++;
        return true;
    } else if(compare_to(newn->data, ll->head->data) < 0) {
        newn->next = ll->head;
        ll->head = newn;
        return true;
    } else {
        node *after = ll->head->next;
        node *before = ll->head;

        while (after != NULL){
            if (compare_to(newn->data, after->data) < 0) break;
            before = after;
            after = after->next;
        }

        newn->next = before->next;
        before->next = newn;
        return true;
    }
    free(newn);
    return false;

}

void linked_list_print(linked_list *ll){ 
    node *current = ll->head;
    while (current != NULL){ 
     printf("%d ", current->data); 
     current = current->next; 
    }
    printf("\n"); 
} 

