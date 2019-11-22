#include <pthread.h>
#include "thread.h"
#include <stdio.h>




int main(int argc, char**argv){
    int i;
    char name[100];
    pthread_t thread_handle[10];

    struct arg targ[10];

    for(i=0;i<10;i++){
        targ[i].i = i;
        targ[i].name = name;
        pthread_create(&thread_handle[i], NULL, child_thread, &targ[i]);
    }
    for(i=0;i<10;i++){
        pthread_join(thread_handle[i],NULL);
    }
    printf("Current value of name is: %s\n",name);

    return 0;

}
