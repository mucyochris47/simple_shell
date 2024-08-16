#include "shell.h"

/**
 * shell_loop - Main loop of the shell.
 */
void shell_loop(void)
{
    char *line = NULL; /* Input line */
    size_t len = 0;   /* Buffer length */
    ssize_t read;      /* Number of characters read */
    char **args;       /* Arguments for command */
    
    while (1)
    {
        /* Display prompt */
        prompt();

        /* Get user input */
        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (feof(stdin)) /* End-of-file (Ctrl+D) */
            {
                printf("\n");
                exit(EXIT_SUCCESS);
            }
            perror("getline");
            exit(EXIT_FAILURE);
        }

        /* Remove newline character from the end of the line */
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        /* Parse the input line into arguments */
        args = parse_command(line);

        /* Check for built-in commands */
        if (built_in_commands(args) == 0)
        {
            /* Execute the command */
            execute_command(line);
        }

        /* Free allocated memory for arguments */
        free_array(args);
    }

    /* Free allocated memory for the line */
    free(line);
}

