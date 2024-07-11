#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    int sem1;

    char a = '5';
    sem1 = semget(1212, 1, IPC_CREAT | 0666); 
    if (sem1 < 0) {
        printf("Semaphore not created");
        return 1;
    }


    semctl(sem1, 0, SETVAL, 1); 

    struct sembuf sem_op;
    FILE *fd;

    fd = fopen("akr", "a");
    if (fd == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    sem_op.sem_num = 0;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;
    semop(sem1, &sem_op, 1);

    putc('\n', fd); 
    putc(a, fd);    

    printf("Press Enter to release the lock :");
    getchar(); 

    fclose(fd);

    sem_op.sem_num = 0;
    sem_op.sem_op = 1;
    sem_op.sem_flg = 0;
    semop(sem1, &sem_op, 1); 

    return 0;
}
