#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "myipc.h"
#include <sys/msg.h>
#include <string.h> /* For strerror(3c) */
#include <errno.h> /* For errno */
#include <unistd.h> /* rand(3c) */
#include <stdio.h>

#define M 10
#define N 8


/**
 * 有一个仓库，可以存放A和B两种产品，仓库的存储空间足够大，但要求:
 * (1)一次只能存入一种产品(A或B);
 * (2)-N < (A产品数量-B产品数量) < M。
 * 其中，N和M是正整数。
 * 试用“存放A”和“存放B”以及P、V操作􏰓述产品A与产品B的入库过程
 * @return
 */
int main (int argc, char **argv) {
    key_t ipckey;
    int semid;
    struct sembuf sem[2]; /* sembuf defined in sys/sem.h */

    /* Generate the ipc key */
    ipckey = ftok("/home/hsu/Desktop/OS", 42);

    /* Set up the semaphore set. 4 == READ, 2 == ALTER */
    semid = semget(ipckey, 1, 0666 | IPC_CREAT);
    if (semid < 0) {
        printf("Error - %s\n", strerror(errno));
        _exit(1);
    }

    /* These never change so leave them outside the loop */
    sem[0].sem_num = 0;
    sem[1].sem_num = 0;
    sem[0].sem_flg = SEM_UNDO; /* Release semaphore on exit */
    sem[1].sem_flg = SEM_UNDO; /* Release semaphore on exit */

    int *shared_1 = 0; /* pointer to the shm */
    int *shared_2 = 0;
    int shmid_1;
    int shmid_2;

    shmid_1 = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    shmid_2 = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);

    if (fork() == 0) { /* A */
        /* Attach to shared memory and print the pointer */
        while(1) { /* loop forever */
            /* Set up two semaphore operations */
            shared_1 = shmat(shmid_1, (void *) 0, 0);
            shared_2 = shmat(shmid_2, (void *) 0, 0);
            sem[0].sem_op = 0; /* Wait for zero */
            sem[1].sem_op = 1; /* Add 1 to lock it*/
            semop(semid, sem, 2);
            printf("[A] I have the semaphore\n");
            /* Critical section */
            if(((int)*shared_1 - (int)*shared_2 < M)){
                printf("[A] Store A\n");
                *shared_1 += 1;
            }else{
                printf("[A] Waiting for B to store\n");
            }
            sem[0].sem_op = -1; /* Decrement to unlock */
            semop(semid, sem, 1);
            printf("[A] Released semaphore\n");
            sleep(rand() % 4);
        }

    } else { /* B */
        /* Attach to shared memory and print the pointer */
        while(1) { /* loop forever */
            shared_1 = shmat(shmid_1, (void *) 0, 0);
            shared_2 = shmat(shmid_2, (void *) 0, 0);
            sem[0].sem_op = 0; /* Wait for zero */
            sem[1].sem_op = 1; /* Add 1 to lock it*/
            semop(semid, sem, 2);
            printf("[B] I have the semaphore\n");
            /* Critical section */
            if(*shared_2 - *shared_1 < N){
                printf("[B] Store B\n");
                *shared_2 += 1;
            }else{
                printf("[B] Waiting for A to store\n");
            }

            sem[0].sem_op = -1; /* Decrement to unlock */
            semop(semid, sem, 1);
            printf("[B] Released semaphore\n");
            sleep(rand() % 3);
        }
    }
}
