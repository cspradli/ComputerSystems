#ifndef thread_h
#define thread_h



struct arg {
    int i;
    char*name;
};

void *child_thread(void * targ);


#endif // thread_h

