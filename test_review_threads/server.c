#include <pthread.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>



void* server_proc(void *arg_in){
    int* arg = (int*) arg_in;
    int client_fd = *arg;
    //free(arg_in);
    char *buff = malloc(100);

    printf("I got another connection fd=%i\n",client_fd);
    for(int i=0;i<10;i++){
        sprintf(buff, "%i\n",i);
        printf(buff);
        send(client_fd,buff, strlen(buff), 0);
        sleep(1);
    }
    close(client_fd);
    free(buff);
    pthread_exit(0);
}


int main(){
    int opt = 1;
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sock < 0){
        perror("Error creating socket: ");
        exit(1);
    }

    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

    struct sockaddr_in my_addr;
    memset(&my_addr, 0, sizeof(struct sockaddr_in));

    my_addr.sin_family = AF_INET; 
    my_addr.sin_addr.s_addr = INADDR_ANY; 
    my_addr.sin_port = htons( 8888 ); 
       
    // Forcefully attaching socket to the port 88888 
    socklen_t slen = sizeof(my_addr);

    if (bind(server_sock, (struct sockaddr *)&my_addr, slen) <0){ perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    if (listen(server_sock, 3) < 0){ // queue of three 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 

    pthread_t tid;

    while(1){
        int new_socket = accept(server_sock, 
                        (struct sockaddr *)&my_addr,
                        &slen);
        if(new_socket < 0) { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        }
        printf("got new connection fd=%i\n",new_socket);
        int tmp_fd = malloc(sizeof(int));
        tmp_fd = new_socket;
        pthread_create(&tid, NULL, server_proc,
                        (void *) &tmp_fd);
    }




} 
