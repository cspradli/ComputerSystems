#include <pthread.h>
#include <unistd.h>
#include "thread.h"
#include <stdio.h>

#include <stdlib.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;


// function to run one thread

void *child_thread(void *targ_in){
    struct arg* targ =  (struct arg*) targ_in;

    srandom(targ->i);
    printf("Thread %i runnning\n", targ->i);

    for(int i=0;i<10;i++){
        int sleep_val = random() % 5;
        sleep(sleep_val);
        printf("Thread %i : %i\n", targ->i , i);
    }

    sleep(1);
    pthread_mutex_lock(&mutex1);
    sprintf(targ->name, "I am thread %i\n", targ->i);
    printf("I am thread %i\n", targ->i);
    pthread_mutex_unlock(&mutex1);
    pthread_exit(0);
}
