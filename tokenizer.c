#include "shell.h"
#include <stdlib.h>
#include <string.h>

/**
 * tokenize_input - Tokenizes an input string into an array of arguments.
 * @input: The input string to tokenize.
 *
 * Return: An array of strings (arguments) or NULL if memory allocation fails.
 */
char **tokenize_input(char *input)
{
    char **tokens = NULL;
    char *token = NULL;
    size_t size = 0;
    size_t i = 0;

    // Use strtok to tokenize the input string
    token = strtok(input, " \t\n");
    while (token != NULL)
    {
        // Reallocate memory for tokens array
        tokens = realloc(tokens, sizeof(char *) * (size + 1));
        if (tokens == NULL)
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        tokens[size] = strdup(token);
        if (tokens[size] == NULL)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        size++;
        token = strtok(NULL, " \t\n");
    }

    // Null-terminate the array of tokens
    tokens = realloc(tokens, sizeof(char *) * (size + 1));
    if (tokens == NULL)
    {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    tokens[size] = NULL;

    return tokens;
}

/**
 * free_tokens - Frees the memory allocated for the array of tokens.
 * @tokens: The array of tokens to free.
 */
void free_tokens(char **tokens)
{
    char **temp = tokens;

    while (*temp)
    {
        free(*temp);
        temp++;
    }
    free(tokens);
}

