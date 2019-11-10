/**
 * Main for Monte-Carlo Pi program
 * 11.07.19
 * CSCI 335
 * Author: Caleb Spradlin
 **/
#include "semaphore_lib.h"
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
int main(int argc, char const *argv[])
{
    
    
    semaphore_init();
    pid_t pids[atoi(argv[1])];
    int i = 0;
    int n = atoi(argv[1]);
    long int total = 0;
    int *shm;

    int shm_id = shmget(IPC_PRIVATE, sizeof(unsigned long int), IPC_CREAT | 0666);
    if (shm_id < 0){
        printf("shmget error\n");
        exit(1);
        
    }

    shm = shmat(shm_id, NULL, 0);
    
    if (shm == (int *) -1){
        perror("shmat error\n");
        exit(1);
    }
    for (i = 0; i < n; i++){
        if ((pids[i] = fork() < 0)){
            perror("fork");
            abort();
        } else if (pids[i] == 0){

            total += calculate_pi(atoi(argv[2]));
            exit(0);
        }

    }
    
}
