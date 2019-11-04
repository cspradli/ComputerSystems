#include "philosopher.h"
#include "semaphore_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc, char**argv){

    semaphore_init(); // initialize semaphorea
    create_5_philosophers();
    printf("argc # %i\n", argc);
    int wait_time = 60;
    if(argc > 1){
        wait_time = atoi(argv[1]);
    }
    printf("PARENT: sleeping for %i seconds\n", wait_time);
    sleep(wait_time);

    kill_5_philosophers();
    sleep(2);  // wait for the childen to die
    semaphore_destroy(); // cleanup all semaphores
    return 0;
}

