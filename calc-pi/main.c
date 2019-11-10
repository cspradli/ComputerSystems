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
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    
    
    //check for correct usage
    if (argc < 3){
        printf("Error- correct usage ./my-pi arg1 arg2\n");
        exit(1);
    }

    pid_t pids[atoi(argv[1])];
    int iter = atoi(argv[2]);
    int n = atoi(argv[1]);
    double total = 0;
    double *shm;

    int shm_id = shmget(IPC_PRIVATE, sizeof(unsigned long int), IPC_CREAT | 0666);
    if (shm_id < 0){
        printf("shmget error\n");
        exit(1);
    }

    shm = (double *) shmat(shm_id, NULL, 0);
    if (shm == (double *) -1){
        printf("error\n");
    }

    for (int i = 0; i < n; i++){
        pid_t temp = fork();
        if (temp < 0){
            printf("error with fork\n");
        }
        if (temp == 0){
            //shm += calculate_pi(atoi(argv[2]));
            double ret = calculate_pi(iter);
            *shm += calculate_pi(iter);
            exit(0);
        } else {
            printf("child %i\n", temp);
            pids[i] = temp;
        }
    }
    printf("num darts = %f\n", *shm);
    printf("pi = %f", 4 * (*shm / iter));
    //printf("pi = %li\n", 4* (shm/iter));
    int status;
    pid_t pid;
    while (n < 0)
    {
        pid = wait(&status);
        printf("Child with pid[%d] exited", pid);
        --n;
    }

    printf("total");
    
}
