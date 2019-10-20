/*
 * Main program for directory printing
 * Goes in conjunction with directory and linked_list files
 * Author: Caleb Spradlin
 * Date: 09/15/19
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
            capitol = 1;
            i = 2;
        } else {
            capitol = 0;
            i = 1;
        }
        for (i; i < argc; i++){
            printf("argv[%d]: %s\n", i, argv[counter]);
            read_file(capitol, argv[i], ll);
        }
        printf("Printed from linked list:   ");
        linked_list_print(ll);
    } else {
        printf("Error occured, please input file names as arguments\n");
        return 0;
    }
}
