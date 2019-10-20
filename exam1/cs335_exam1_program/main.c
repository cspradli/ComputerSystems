#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// ERROR there was no import of secret_words .h file
#include "secret_words.h"
#include "linked_list.h"


int main(int argc, char**argv){
	int i,j;
	linked_list*ll;
	node*n;
	char buffer[100];
	FILE * fp;
	int len;
	
	ll = linkedlist_initialize();

	if(argc == 1){
		printf("No files given on the command line\n");
		exit(1);
	}else{
		//read in each file from the command line
		for(i=1; i<argc; i++){
            printf("Reading file %s\n",argv[i]);
			fp = fopen(argv[i],"r");
			
			if(fp){
				while(fgets(buffer,100,fp)){
					len = strlen(buffer);
                    if(buffer[len-1] == '\n') buffer[len-1] = '\0';//removes the newline
					linkedlist_add(ll,buffer);
					//linkedlist_add__insert_sort(ll,buffer);
				}
				fclose(fp);
			}else{
				printf("could not open %s\n",argv[i]);
			}
		}
	}
	printf("File has %i lines\n",ll->count);	

    // Secret words
    int num_secret_words = number_of_secret_words();
    char * current_secret_word;
    int count = 0;
    int case_count = 0;

    for(j=0; j<num_secret_words; j++){
        current_secret_word = get_secret_word(j);
        //printf("Secret word %i is '%s'\n",j,current_secret_word);
        printf("Secret word %i is %zu charcters long\n",j,strlen(current_secret_word));

        // search through the list for the secret word
        count = 0;
        case_count = 0;
        for( n = ll->head; n->next != NULL; n=n->next){
            if(strstr(n->data,current_secret_word) != NULL){ count++; }
            if(strcasestr(n->data,current_secret_word) != NULL){
		    // ERROR this was count instead of case_count
		    case_count++; }
        }
        printf("Number of lines with this word is: %i\n",count);
        printf("Number of lines with this word is: %i (case insensitive)\n",case_count);
    }

	// clean up
	linkedlist_destory(ll);

	return 0;
}
