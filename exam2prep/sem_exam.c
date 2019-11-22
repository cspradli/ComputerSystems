

struct sembuf operation;
int lock;

void create_lock(){
    operation.sem_num=0;
    operation.sem_flg=0;
    lock = semget(ftok(".",42), 1, IPC_PRIVATE | IPC_CREAT | 0666);
    union semun {int val; struct semid
