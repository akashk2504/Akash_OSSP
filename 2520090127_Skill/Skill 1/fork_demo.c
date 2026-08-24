#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Original Process: PID = %d, PPID = %d\n", getpid(), getppid());

    pid = fork(); // create child process

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child Process: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(5); // simulate waiting state
        printf("Child Process (after sleep): PID = %d, PPID = %d\n", getpid(), getppid());
    } else {
        // Parent process
        printf("Parent Process: PID = %d, PPID = %d\n", getpid(), getppid());
        wait(NULL); // parent waits for child
        printf("Parent Process (after child termination): PID = %d, PPID = %d\n", getpid(), getppid());
    }

    return 0;
}

