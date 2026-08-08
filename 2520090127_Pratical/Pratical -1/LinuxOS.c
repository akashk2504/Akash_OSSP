#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char command[100];
    pid_t pid;

    printf("Enter a Linux command: ");
    fgets(command, sizeof(command), stdin);

    // Remove newline character from input
    command[strcspn(command, "\n")] = 0;

    pid = fork(); // Create child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child Process PID: %d\n", getpid());
        execlp(command, command, (char *)NULL); // Execute command
        perror("exec failed"); // If exec fails
        exit(1);
    } else {
        // Parent process
        printf("Parent Process PID: %d\n", getpid());
        wait(NULL); // Wait for child to finish
        printf("Child process finished execution.\n");
    }

    return 0;
}

