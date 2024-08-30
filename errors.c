#include "shell.h"

/**
 * print_err_str - outputs a string to stderr
 * @string: the string to be output
 *
 * Return: Nothing
 */
void print_err_str(char *string)
{
    int index = 0;

    if (!string)
        return;
    while (string[index] != '\0')
    {
        write_err_char(string[index]);
        index++;
    }
}

/**
 * write_err_char - writes a single character to stderr
 * @char_to_write: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_err_char(char char_to_write)
{
    static int count;
    static char buffer[WRITE_BUF_SIZE];

    if (char_to_write == BUF_FLUSH || count >= WRITE_BUF_SIZE)
    {
        write(2, buffer, count);
        count = 0;
    }
    if (char_to_write != BUF_FLUSH)
        buffer[count++] = char_to_write;
    return (1);
}

/**
 * write_char_fd - writes a character to a specified file descriptor
 * @char_to_write: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_char_fd(char char_to_write, int fd)
{
    static int count;
    static char buffer[WRITE_BUF_SIZE];

    if (char_to_write == BUF_FLUSH || count >= WRITE_BUF_SIZE)
    {
        write(fd, buffer, count);
        count = 0;
    }
    if (char_to_write != BUF_FLUSH)
        buffer[count++] = char_to_write;
    return (1);
}

/**
 * print_str_fd - prints a string to a specified file descriptor
 * @string: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int print_str_fd(char *string, int fd)
{
    int count = 0;

    if (!string)
        return (0);
    while (*string)
    {
        count += write_char_fd(*string++, fd);
    }
    return (count);
}

