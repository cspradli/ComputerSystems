#include <stdio.h>
#include "linked_list.h"

int main(int argc, char**argv){
    linked_list* ll;
    node* n;
    int i;
    char buffer[100];

    ll = create_linked_list(); // create the list
    
    // add 10 items
    for(i = 0; i < 10; i++){
        sprintf(buffer, "item %i", i);
        linked_list_add(ll, buffer);
    }
    
    // print list
    for(i=0; i< ll->count; i++){
        n = linked_list_get(ll, i);
        printf("%i %s\n", i, n->data);
    }
    // search for item
    n = linked_list_search(ll, "item 5");
    // delete item
    linked_list_delete(ll, n);
    //print list
    for(i=0; i< ll->count; i++){
        n = linked_list_get(ll, i);
        printf("%i %s\n", i, n->data);
    }
    //print list using print function
    linked_list_print(ll);
    linked_list_destroy(ll);

    return 0;
}
