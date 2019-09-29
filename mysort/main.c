/*
 * Main program for directory printing
 * Goes in conjunction with directory and linked_list files
 * Author: Caleb Spradlin
 * Date: 09/15/19
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "file_input.h"

int main(int argc, char *argv[]) {
    linked_list *ll;
    ll = create_linked_list();
    if (argc > 1) {
        printf("Printing directory of: %s\n", argv[1]);
	    int counter = 0;
	    for (counter = 1; counter < argc; counter++){
		    read_ints(ll, argv[counter]);
		    printf("argv[%d]: %s", counter, argv[counter]);
	    }
        linked_list_print(ll);
    } else {
        printf("Error occured, please input file names as arguments\n");
        return 0;
    }
}
