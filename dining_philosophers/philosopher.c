#include "semaphore_lib.h"
#include "philosopher.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define N 5

int chopsticks[5];
pid_t philosopher_pid[5];
int eat_count = 0;
int think_count = 0;

int pickup_chopstick(int which_stick){
    // try to pick up chopstick 'which_stick' [0-4]
    pid_t pid = getpid();
    printf("Child[%i] pickup_chopstick(%i)\n",pid,which_stick);
    fflush(stdout);
    usleep(10000); // 0.1 seconds?
    return semaphore_lock(which_stick);
}

int setdown_chopstick(int which_stick){
    pid_t pid = getpid();
    printf("Child[%i] pickup_chopstick(%i)\n",pid,which_stick);
    fflush(stdout);
    usleep(10000);
    return semaphore_unlock(which_stick);
}

void eat_from_plate(){ //check for # of args{
    pid_t pid = getpid();
    printf("Child[%i] eating\n",pid);
    fflush(stdout);
    eat_count++;
    sleep(1);
}

void think(){
    pid_t pid = getpid();
    printf("Child[%i] thinking\n",pid);
    fflush(stdout);
    think_count++;
    sleep(1);
}


void sigterm_handler(int sig_num){
    pid_t mypid = getpid();
    printf("Child[%i] eat_count=%i think_count=%i\n",mypid, eat_count, think_count);
    fflush(stdout);
    exit(0);
}


void sigchild_handler(int sig_num){
    int status;
    pid_t pid;
    while((pid = waitpid(-1, &status, WNOHANG|WCONTINUED)) > 0){
        printf("Child %i exited with status %i\n",pid, status);
    }
}


void create_5_philosophers(int argc){
    // initialize chopsticks
    int i;
    for(i=0;i<5;i++){
        chopsticks[i] = create_semaphore(i);
    }
    // set sigterm handler
    if( signal(SIGTERM, sigterm_handler) == SIG_ERR){
        printf("Error setting SIGTERM handler\n");
        exit(1);
    }
    // create 5 philosophers processes 
    for(i=0;i<5;i++){
        pid_t temp = fork();
        if (temp == 0){
            if (argc > 1){ //check for # of args
                printf("Using corrected algorithm\n");
                printf("%i\n", i);
                fflush(stdout);
                philosopher_algorithm_cr(i);
            } else {
                printf("Using deadlock algorithm\n");
                fflush(stdout);
                philosopher_algorithm(i);
            }
            exit(0);
        }else{
            philosopher_pid[i] = temp;
        }
    }
    if( signal(SIGCHLD, sigchild_handler) == SIG_ERR){
        printf("Error setting SIGCHLD handler\n");
    }
}


void test(int num){
    //if neighbors aren't eating then eat 
    // next philosopher eats 
    //



}
void kill_5_philosophers(){
    int i;
    for(i=0;i<5;i++){
        printf("Sending SIGTERM to child %i\n", philosopher_pid[i]);
        kill( philosopher_pid[i], SIGTERM);
    }
}

void philosopher_algorithm(int num){
    int chopstick1 = chopsticks[num];
    int chopstick2 = chopsticks[(num+1)%5];

    pid_t pid = getpid();
    printf("Child[%i] starting philosopher_algorithm(%i)\n",pid,num);
    fflush(stdout);

    while(1){ // basic algorithm
        pickup_chopstick( chopstick1 );
        printf("Got left chopstick\n");
        pickup_chopstick( chopstick2 );
        printf("Got left chopstick\n");
        eat_from_plate();
        setdown_chopstick( chopstick1 );
        setdown_chopstick( chopstick2 );
        think();
    }

}

void philosopher_algorithm_cr(int num){
    //int chopstick1 = chopsticks[i];
    //int chopstick2 = chopsticks[(i+1)%5];

    pid_t pid = getpid();
    printf("Child[%i] starting corrected philosopher_algorithm(%i)\n", pid, num);
    fflush(stdout);
    int left = num;
    int right = (num + 1) % N;
    
    if (left > right){
        left = right;
        right = left + 1;
    }

    int chopstick1 = chopsticks[left];
    int chopstick2 = chopsticks[right];
    
    while(1){

        pickup_chopstick( chopstick1 );
        printf("Philosopher[%i] picked up left chopstick\n", num);
        fflush(stdout);
        pickup_chopstick( chopstick2 );
        printf("Philosopher[%i] picked up right chopstick\n", num);
        fflush(stdout);
        eat_from_plate();
        setdown_chopstick(chopstick1);
        setdown_chopstick(chopstick2);
        think();
    }

}






