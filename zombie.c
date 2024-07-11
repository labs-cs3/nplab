#include <stdio.h>
#include <unistd.h>

int main() {
    int pid;
    pid = fork();

    if (pid < 0) {
        printf("fork failed\n");
    } else if (pid == 0) {
        printf("This is the child process with PID %d\n", getpid());
        printf("Parent process ID for the child is %d\n", getppid());
    } else {
        sleep(20);
        printf("This is the parent process with PID %d\n", getpid());
    }
    return 0;
}