#include "shell.h"

/**
 * parse_command - Parses a command string into arguments
 * @command: The command string to parse
 * @argv: Array to store the parsed arguments
 * Return: Number of arguments parsed
 */
int parse_command(char *command, char **argv)
{
    int argc = 0;
    char *token;

    if (command == NULL)
        return 0;

    token = strtok(command, " \t\n");
    while (token != NULL)
    {
        argv[argc++] = token;
        token = strtok(NULL, " \t\n");
    }
    argv[argc] = NULL;  // Null-terminate the argument list

    return argc;
}

/**
 * handle_input - Reads and parses input from the user
 * @input: Buffer to store the input
 * @size: Size of the buffer
 * Return: Number of characters read
 */
ssize_t handle_input(char *input, size_t size)
{
    ssize_t bytes_read;

    bytes_read = getline(&input, &size, stdin);
    if (bytes_read == -1)
    {
        perror("getline");
        exit(EXIT_FAILURE);
    }

    // Remove newline character if present
    if (bytes_read > 0 && input[bytes_read - 1] == '\n')
        input[bytes_read - 1] = '\0';

    return bytes_read;
}

/**
 * split_input - Splits the input into commands based on delimiters
 * @input: The input string to split
 * @commands: Array to store the split commands
 * Return: Number of commands split
 */
int split_input(char *input, char **commands)
{
    int count = 0;
    char *token;

    if (input == NULL)
        return 0;

    token = strtok(input, ";");
    while (token != NULL)
    {
        commands[count++] = token;
        token = strtok(NULL, ";");
    }
    commands[count] = NULL;  // Null-terminate the command list

    return count;
}

