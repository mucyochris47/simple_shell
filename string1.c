#include "shell.h"

/**
 * clone_string - duplicates the content of a source string into a destination buffer
 * @dest: the buffer to hold the duplicated string
 * @src: the source string to copy from
 *
 * Return: pointer to the destination buffer
 */
char *clone_string(char *dest, const char *src)
{
    int idx = 0;

    if (dest == src || src == NULL)
        return dest;

    while (src[idx])
    {
        dest[idx] = src[idx];
        idx++;
    }
    dest[idx] = '\0'; // Ensure null termination
    return dest;
}

/**
 * create_string_copy - allocates memory and copies a string to it
 * @input: the string to copy
 *
 * Return: pointer to the newly allocated string
 */
char *create_string_copy(const char *input)
{
    int length = 0;
    char *new_string;

    if (input == NULL)
        return NULL;

    while (input[length])
        length++;

    new_string = malloc(sizeof(char) * (length + 1));
    if (!new_string)
        return NULL;

    for (length++; length--;)
        new_string[length] = input[length];

    return new_string;
}

/**
 * display_string - prints a string to the standard output
 * @str: the string to print
 *
 * Return: Nothing
 */
void display_string(const char *str)
{
    int i = 0;

    if (str == NULL)
        return;

    while (str[i] != '\0')
    {
        output_char(str[i]);
        i++;
    }
}

/**
 * output_char - writes a single character to the standard output
 * @c: the character to write
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int output_char(char c)
{
    static int buffer_index;
    static char buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
    {
        write(1, buffer, buffer_index);
        buffer_index = 0;
    }
    if (c != BUF_FLUSH)
        buffer[buffer_index++] = c;

    return 1;
}

