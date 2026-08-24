#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    printf("Parent PID=%d starting...\n", getpid());

    // --- Part 1: Create multiple children ---
    for (int i = 0; i < 3; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process
            printf("Child %d: PID=%d, PPID=%d\n", i, getpid(), getppid());
            sleep(2 + i); // simulate work
            exit(100 + i); // exit with unique status
        }
    }

    // --- Part 2: Synchronization using wait() ---
    printf("\n[Using wait()]\n");
    while ((pid = wait(&status)) > 0) {
        printf("wait(): Child PID=%d exited with status=%d\n", pid, WEXITSTATUS(status));
    }

    // --- Part 3: Zombie process demonstration ---
    printf("\n[Zombie Process Demo]\n");
    pid = fork();
    if (pid == 0) {
        printf("Zombie Child PID=%d exiting...\n", getpid());
        exit(0); // child exits immediately
    } else {
        printf("Parent PID=%d sleeping (child becomes zombie)...\n", getpid());
        sleep(10); // during this time, child is zombie
        // Run `ps -l` in another terminal to observe zombie state
    }

    // --- Part 4: Eliminating zombie using waitpid() ---
    printf("\n[Fixing Zombie with waitpid()]\n");
    pid = fork();
    if (pid == 0) {
        printf("Child PID=%d exiting...\n", getpid());
        exit(0);
    } else {
        waitpid(pid, &status, 0); // parent reaps child immediately
        printf("Parent reaped child PID=%d, status=%d\n", pid, WEXITSTATUS(status));
        sleep(5); // no zombie remains
    }

    return 0;
}

