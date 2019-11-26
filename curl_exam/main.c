#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "mycurl.h"

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

struct arg {
    linked_list *ll;
    char*name;
};
typedef struct thread_data
{
    linked_list *ll;
    char*name;

} thread_data;

void *thread(void *targ_in);

int main(int argc, char**argv){
    pthread_t tid;
    char* urls[10] = {
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check1.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check2.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check3.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check4.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check5.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check6.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check7.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check8.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check9.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check10.php"
    };
    int i;

    linked_list* my_list = create_linked_list();
    thread_data *tdata;
    tdata = malloc(sizeof(tdata));
    for(i=0; i< 10; i++){
        tdata->ll = my_list;
        tdata->name=urls[i];
        printf("%s\n",urls[i]);
        pthread_create(&tid, NULL, thread, (void *)&tdata);
    }



    // print out list
    node* n;
    for(i=0; i < my_list->count; i++){
        n = linked_list_get(my_list, i);
        printf("[%i] %s\n", i, n->data);
    }
    // clean up
    destroy_linked_list( my_list );
    return 0;
}


void *thread(void *targ_in){
        struct arg* targ = (struct arg*) targ_in;
        pthread_mutex_lock(&mutex1);
        
        char *output = parse_and_fetch_url(targ->name);
        linked_list_add(targ->ll, output);
        pthread_mutex_unlock(&mutex1);
        pthread_exit(NULL);
}


