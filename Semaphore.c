#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h> 
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/sem.h>

#define NUM_LOOPS 20
int main(int argc, char * argv[]) {
    int sem_set_id;
    nt child_pid;
    int i;
    struct sembuf sem_op;
    int rc;
    int val;
    sem_set_id = semget(IPC_PRIVATE, 1, 0600);
    if (sem_set_id == -1) {
        perror("main: semget");
        exit(1);
    }
    printf("Semaphore set created, semaphore set id '%d'.n", sem_set_id);
    rc = semctl(sem_set_id, 0, SETVAL, 0);
    child_pid = fork();
    switch (child_pid) {
    case -1:
        perror("fork");
        exit(1);
    case 0:
        for (i = 0; i < NUM_LOOPS; i++) {
            sem_op.sem_num = 0;
            sem_op.sem_op = -1;
            sem_op.sem_flg = 0;
            semop(sem_set_id, & sem_op, 1);
            printf("consumer: '%d\n", i);
            val = semctl(sem_set_id, 0, GETVAL, 0);
            printf("consumer after completion %d\n", val);
            fflush(stdout);
            sleep(3);
        }
        break;
    default:
        for (i = 0; i < NUM_LOOPS; i++) {

            printf("producer: '%d\n", i);
            fflush(stdout);
            sem_op.sem_num = 0;
            sem_op.sem_op = 1;
            sem_op.sem_flg = 0;
            semop(sem_set_id, & sem_op, 1);
            val = semctl(sem_set_id, 0, GETVAL, 0);
            sleep(2);
            printf(" producer after completion %d\n", val);
        }
        break;
    }
    return 0;
}