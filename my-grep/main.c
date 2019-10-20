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
    char *key;
    int capitol = 0;
    int i = 0;
    char *checkI = "-i";
    if (argc > 1) {
	    int counter = 0;
        if(strcmp(argv[1], checkI) == 0){
            key = argv[1];
            capitol = 1;
            i = 2;
        } else {
            key = NULL;
            capitol = 0;
            i = 1;
        }
        for (i; i < argc; i++){
            printf("argv[%d]: %s\n", i, argv[counter]);
            read_file(capitol, argv[i], key,ll);
        }
        printf("Printed from linked list:   ");
        linked_list_print(ll);
    } else {
        printf("Error occured, please input file names as arguments\n");
        return 0;
    }
}
