#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
/*
struct my_struct {    
	int num;
};

int main(int argc, char**argv){    
	struct my_struct* s;    
	fprintf(stderr, "Before"); 
	fflush(stderr);
	s->num = 4;    
	printf("After");    
	return 0;
	}

int main(int argc, char const *argv[])
{
	printf("%i", fork());
}
*/
/*
int main(int argc, char**argv){int status;printf("%s\n", "Hello");printf("%d\n", !fork());if(wait(&status) != -1)printf("%d\n", WEXITSTATUS(status));printf("%s\n", "Bye");exit(2);}
*/
/*
void sigchild_handler(int sig){
    int status;
    pid_t pid;
    while((pid = waitpid(-1,&status,WNOHANG|WCONTINUED)) > 0){
        printf("Pid=%i, exited with status=%i\n",pid,status);
    }
}
int main(int argc, char**argv){
    int i;
    signal(SIGCHLD, sigchild_handler);
    for(i=0;i<10;i++){
        pid_t pid = fork();
        if(pid){
            sleep(10);
        }else{
            printf("%i\n",getpid());
            sleep(1);
            exit(0);
        }
    }
}*/
/*
int main(int argc, char**argv){
    int i;
    for(i=0;i<5;i++){
        if(fork() == 0){
            printf("%i",i);
            exit(0);
        }
    }
    pid_t pid;
    int status;
    while((pid = wait(&status))>0){ }
    printf("\n");
}*/
/*
	pid_t pid;
	void handler1(int sig) {
	 	 printf("zip ");
	 	 fflush(stdout);  Flushes the printed string to stdout 
	 	 kill(pid, SIGUSR1);
	}
	void handler2(int sig) {
	 	 printf("zap ");
	 	 exit(0);
	}
	int main() {
		signal(SIGUSR1, handler1);
		if ((pid = fork()) == 0) {
			signal(SIGUSR1, handler2);
			kill(getppid(), SIGUSR1);
			while(1) {};
		}else {
			pid_t p; int status;
			if ((p = wait(&status)) > 0) {
				printf("zoom ");
			}
		}
	}
*/
/*
	 void doit() {
	 	 if (fork() == 0) {
	 	 	 fork();
	 	 	 printf("hello\n");
		}
	 	 printf("hello\n");
	}
	 int main() {
	 	 doit();
	 	 printf("hello\n");
	 	 exit(0);
	}
*/
/*
	int counter = 0;
	void handler(int sig){
		counter ++;
	}
	int main(){
		int i;
		signal(SIGCHLD, handler);
		for (i = 0; i < 5; i ++){
			if (fork() == 0){
				exit(0);
			}
		}
		 wait for all children to die 
		while (wait(NULL) != -1);
		printf("counter = %d\n", counter);
		return 0;
	}

*/

struct sembuf operation;
int lock;
void create_lock(){
    operation.sem_num=0;
    operation.sem_flg=0;
    lock = semget(ftok(".",42), 1, IPC_PRIVATE | IPC_CREAT | 0666);
    union semun {int val; struct semid_ds *buf; ushort * array; } argument;
    argument.val = 3;
    semctl(lock, 0 , SETVAL, argument);
}
void get_lock(){
    operation.sem_op = -1;
    semop(lock, &operation, 1);
}
void release_lock(){
    operation.sem_op = 1;
    semop(lock, &operation, 1);
}
int main(int argc, char**argv){
    int i, status, val=0, count=5;
    pid_t t;
    if(argc > 1) count = atoi(argv[1]);
    create_lock();
    for(i=0; i<count; i++){
        if((t = fork())==0){
            get_lock();
            exit(0);
            release_lock();
        }else{
            sleep(1);
            kill(t, SIGTERM);
            waitpid(t, &status, 0);
            if(!status) val++;
        }
    }
    printf("val = %d\n",val);
}