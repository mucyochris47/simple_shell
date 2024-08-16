#include "shell.h"

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: A pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
    char *dup;
    size_t len = strlen(str) + 1;

    dup = malloc(len);
    if (!dup)
        return (NULL);

    memcpy(dup, str, len);
    return (dup);
}

/**
 * _strtok - Tokenizes a string using a delimiter.
 * @str: The string to tokenize.
 * @delim: The delimiter string.
 *
 * Return: A pointer to the next token, or NULL if no more tokens.
 */
char *_strtok(char *str, const char *delim)
{
    static char *next_token = NULL;
    char *start;
    size_t len;

    if (str)
        next_token = str;

    if (!next_token)
        return (NULL);

    start = next_token;

    /* Find the end of the token */
    while (*next_token && !strchr(delim, *next_token))
        next_token++;

    /* If we found a token, null-terminate it */
    if (*next_token)
    {
        *next_token = '\0';
        next_token++;
    }
    else
    {
        next_token = NULL;
    }

    return (start);
}

/**
 * _strlen - Computes the length of a string.
 * @str: The string.
 *
 * Return: The length of the string.
 */
size_t _strlen(const char *str)
{
    const char *s;

    for (s = str; *s; s++)
        ;

    return (s - str);
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: An integer less than, equal to, or greater than zero, according to
 *         whether s1 is less than, equal to, or greater than s2.
 */
int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }

    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

