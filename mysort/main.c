/*
 * Main program for directory printing
 * Goes in conjunction with directory and linked_list files
 * Author: Caleb Spradlin
 * Date: 09/15/19
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "directory.h"

int main(int argc, char *argv[]) {

    if (argc > 1) {
        printf("Printing directory of: %s\n", argv[1]);
	int counter = 0;
	for (counter = 1; counter < argc; counter++){
		read_file(argv[counter]);
		printf("argv[%d]: %s", counter, argv[counter]);
	}
    } else {
        printf("Error occured, please input file names as arguments\n");
        return 0;
    }
}
