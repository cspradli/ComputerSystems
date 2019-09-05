#include <stdio.h>
#include "linked_list.h"

int main(int argc, char**argv){
    linked_list* ll;
    node* n;
    int i;
    char buffer[100];

    ll = create_linked_list(); // create the list
    
    linked_list_add(ll, "item 1");
    linked_list_add(ll, "item 2");
    linked_list_add(ll, "item 3");
    linked_list_add(ll, "item 4");
    linked_list_add(ll, "item 5");
    linked_list_add(ll, "item 6");
    linked_list_add(ll, "item 7");
    linked_list_add(ll, "item 8");
    linked_list_add(ll, "item 9");
    linked_list_add(ll, "item 10");
    
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

    return 0;
}
