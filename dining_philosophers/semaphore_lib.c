#include "semaphore_lib.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/sem.h>
#include <stdio.h>



int all_locks[5];

void semaphore_init(){
    int i;
    for(i=0;i<5;i++){
        all_locks[i] = 0;
    }
}

void semaphore_destroy(){
    int i;
    for(i=0;i<5;i++){
        if(semctl( all_locks[i], 0, IPC_RMID ) < 0){
            perror("semctl");
            exit(1);
        }
    }
}

int semaphore_lock(int lock_num){
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = 0;

    return semop(lock_num, &op, 1);
}

int semaphore_unlock(int lock_num){
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;

    return semop(lock_num, &op, 1);
}

int create_semaphore(int sem_count){
    key_t semkey = ftok(".", (1234)+sem_count);
    int lock = semget(semkey, 1, IPC_PRIVATE | IPC_CREAT | 0666);

    union semun {
        int val;
        struct semid_ds *buf;
        ushort *array;
    } argument;
    argument.val = 1;

    if( semctl( lock, 0, SETVAL, argument ) < 0){
        perror("semctl");
        exit(1);
    }

    all_locks[sem_count] = lock;

    return lock;
}


