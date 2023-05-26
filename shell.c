#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

int main(void) {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("$ ");
        fflush(stdout);  // Flush stdout to ensure prompt is displayed

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            break;  // Exit the loop on end-of-file
        }

        // Remove trailing newline character from the command
        command[strcspn(command, "\n")] = '\0';

        // Fork a child process
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process

            // Execute the command using the shell
            execlp(command, command, (char *)NULL);

            // If execlp returns, an error occurred
            perror("execlp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process

            // Wait for the child process to complete
            wait(NULL);
        }
    }

    return 0;
}

