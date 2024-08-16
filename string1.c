#include "shell.h"

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string to append.
 *
 * Return: A pointer to the resulting concatenated string.
 */
char *_strcat(char *dest, const char *src)
{
    char *ptr = dest;

    // Move to the end of the destination string
    while (*ptr)
        ptr++;

    // Append source string to destination string
    while (*src)
        *ptr++ = *src++;

    // Null-terminate the resulting string
    *ptr = '\0';

    return (dest);
}

/**
 * _strncat - Concatenates up to n characters from source string to destination string.
 * @dest: The destination string.
 * @src: The source string to append.
 * @n: The maximum number of characters to append.
 *
 * Return: A pointer to the resulting concatenated string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
    char *ptr = dest;

    // Move to the end of the destination string
    while (*ptr)
        ptr++;

    // Append up to n characters from the source string
    while (n-- && *src)
        *ptr++ = *src++;

    // Null-terminate the resulting string
    *ptr = '\0';

    return (dest);
}

/**
 * _strchr - Locates the first occurrence of a character in a string.
 * @str: The string to search.
 * @c: The character to locate.
 *
 * Return: A pointer to the first occurrence of the character, or NULL if not found.
 */
char *_strchr(const char *str, int c)
{
    while (*str != (char)c)
    {
        if (*str == '\0')
            return (NULL);
        str++;
    }

    return ((char *)str);
}

/**
 * _strncpy - Copies up to n characters from source string to destination string.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 *
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
    char *ptr = dest;

    // Copy up to n characters from the source string
    while (n-- && *src)
        *ptr++ = *src++;

    // Null-fill the rest of the destination string if n is not exhausted
    while (n--)
        *ptr++ = '\0';

    return (dest);
}

