#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define KEY (1492)

int main(int argc, char**argv){
    int id;

    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } argument;
    // how many concurrent processes?
    argument.val = 1;
    // initialize the semaphore
    id = semget(KEY, 1, 0666 | IPC_CREAT);
    semctl(id, 0, SETVAL, argument);

    // setup the ops struct
    struct sembuf operations[1];
    operations[0].sem_num = 0; //which semaphore
    operations[0].sem_op = -1;  // incriment/decriment
    operations[0].sem_flg = 0;  // no flags

    pid_t pid;
    if((pid = fork()) == 0){
        // child
        sleep(1);
        printf("CHILD: trying to get lock\n");
        semop(id, operations, 1);
        printf("CHILD: got lock\n");
        exit(0);
    }else{
        // parent
        printf("PARENT: trying to get lock\n");
        semop(id, operations, 1);
        printf("PARENT: got lock\n");
        sleep(10);
        return 0;
    }
}
