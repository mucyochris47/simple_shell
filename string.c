#include "shell.h"

/**
 * get_str_length - calculates the length of a given string
 * @str: the string whose length to determine
 *
 * Return: integer length of the string
 */
int get_str_length(char *str)
{
    int len = 0;

    if (!str)
        return (0);

    while (*str++)
        len++;
    return (len);
}

/**
 * lex_compare - performs lexicographic comparison of two strings
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int lex_compare(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}

/**
 * find_start - checks if the prefix is at the beginning of the string
 * @haystack: the string to search within
 * @prefix: the prefix to look for
 *
 * Return: address of the next char after prefix in haystack, or NULL
 */
char *find_start(const char *haystack, const char *prefix)
{
    while (*prefix)
    {
        if (*prefix++ != *haystack++)
            return (NULL);
    }
    return ((char *)haystack);
}

/**
 * append_str - appends the source string to the destination buffer
 * @dest: the destination buffer
 * @src: the source string to append
 *
 * Return: pointer to the destination buffer
 */
char *append_str(char *dest, char *src)
{
    char *start = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = '\0';
    return (start);
}

