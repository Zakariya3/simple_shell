#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

void shell(void)
{
	char command[MAX_COMMAND_LENGTH];
	int status;

	while (1)
	{
		printf("$ ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			if (feof(stdin))
			{
				printf("\n");
				break; /* End of file (Ctrl+D) reached */
			}
		}

		command[strcspn(command, "\n")] = '\0'; /* Remove newline character */

		pid_t pid = fork();

		if (pid < 0)
		{
			printf("Failed to create child process\n");
			continue;
		}
		else if (pid == 0)
		{
			/* Child process */
			execlp(command, command, NULL);

			/* Execution failed */
			printf("%s: command not found\n", command);
			exit(EXIT_FAILURE);
		}
		else
		{
			/* Parent process */
			waitpid(pid, &status, 0);

			if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			{
				continue;
			}
			else
			{
				printf("Error executing command: %s\n", command);
			}
		}
	}
}

int main(void)
{
	shell();
	return 0;
}

