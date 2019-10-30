#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char**argv){
    pid_t pid;
    int pipefd[2]; // File descriptors for the pipe
    char * buffer;
    int i;

    if( pipe(pipefd) != 0){
        // pipe() did not succeed
        printf("error creating pipes\n");
        return 1;
    }
    if(argc < 2){
        printf("Need input\n");
        return 1;
    }

    if((pid = fork()) == 0){
        // Child
        // child closes the write end of the pipe
        close(pipefd[1]);
        sleep(10);
        printf("I am the child\n");
        char buff_in;
        while( read(pipefd[0], &buff_in, 1) > 0 ){
            //printf("CHILD: read one byte\n");
            //fflush(stdout);
        }
        close(pipefd[0]);
        exit(0);

    }else{
        // Parent
        printf("I am the parent, child pid = %i\n",pid);
        // Parent closes the read end of the pipe
        close(pipefd[0]);
        // allocate space for the buffer
        buffer = (char *) malloc(strlen(argv[1]));
        strcpy(buffer, argv[1] );
        int wrote_amt;
        int total_wrote = 0;
        for(i=0; i< 10240; i++){
        //for(i=0; i< strlen(argv[1]); i++){
            //write(pipefd[1], &buffer[i], 1);
            wrote_amt = write(pipefd[1], &buffer[0], strlen(argv[1]) );
            total_wrote += wrote_amt;
            printf("PARENT: wrote %i byte(s) to the pipe (%i total)\n",wrote_amt,total_wrote);
            fflush(stdout); // make sure data is written to terminal
        }
        close(pipefd[1]); // Done with the pipe, send EOF
        int status;
        waitpid(pid, &status, 0);
        printf("PARENT: child exited with status=%i\n",status);
        return 0;
    }

}
