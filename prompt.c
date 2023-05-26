#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t characters_read;

    printf("$ ");
    fflush(stdout);  // Flush stdout to ensure prompt is displayed

    // Read input line by line
    while ((characters_read = getline(&line, &bufsize, stdin)) != -1)
    {
        printf("%s", line);  // Print the entered command
        printf("$ ");
        fflush(stdout);  // Flush stdout for the next prompt
    }

    free(line);  // Free dynamically allocated memory

    return 0;
}
