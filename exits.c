#include "shell.h"

/**
 * copy_str - copies a string to a destination buffer
 * @dest: the destination buffer
 * @src: the source string
 * @n: the number of characters to copy
 * Return: the destination buffer
 */
char *copy_str(char *dest, char *src, int n)
{
    int index;
    char *start = dest;

    index = 0;
    while (src[index] != '\0' && index < n - 1)
    {
        dest[index] = src[index];
        index++;
    }
    if (index < n)
    {
        while (index < n)
        {
            dest[index] = '\0';
            index++;
        }
    }
    return (start);
}

/**
 * concat_str - concatenates a source string to a destination buffer
 * @dest: the destination buffer
 * @src: the source string
 * @n: the maximum number of bytes to use from the source string
 * Return: the destination buffer
 */
char *concat_str(char *dest, char *src, int n)
{
    int dest_len, src_len;
    char *start = dest;

    dest_len = 0;
    while (dest[dest_len] != '\0')
        dest_len++;
    
    src_len = 0;
    while (src[src_len] != '\0' && src_len < n)
    {
        dest[dest_len] = src[src_len];
        dest_len++;
        src_len++;
    }
    if (src_len < n)
        dest[dest_len] = '\0';
    
    return (start);
}

/**
 * find_char - locates a character in a string
 * @str: the string to be searched
 * @ch: the character to find
 * Return: a pointer to the character in the string, or NULL if not found
 */
char *find_char(char *str, char ch)
{
    while (*str != '\0')
    {
        if (*str == ch)
            return (str);
        str++;
    }
    return (NULL);
}

