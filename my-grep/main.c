/*
 * Main program for my-grep
 * Goes in conjunction with file_input and linked_list files
 * Author: Caleb Spradlin
 * Date: 10/15/19
 */

#include "file_input.h"

int main(int argc, char *argv[]) {
    linked_list *ll;
    ll = create_linked_list();
    char *key = NULL;
    int capitol = 0;
    int i = 0;
    char *checkI = "-i";
    if (argc > 1) {

	//check for -i arg
        if(strcmp(argv[1], checkI) == 0){
            //key search word
	    key = argv[2];
	    //check for Capitolization
            capitol = 1;
            //bump i up to start for loop
	    i = 3;
        } else {
            key = argv[1];
            capitol = 0;
            i = 2;
        }
        for (i; i < argc; i++){
            //printf("argv[%d]: %s", i, argv[i]);
            read_file(capitol, argv[i], key, ll);
        }
        printf("Printed from linked list:\n");
        linked_list_print(ll);
    } else {
        printf("Error occured, please input file names as arguments\n");
        return 0;
    }
}
