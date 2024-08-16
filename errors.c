#include "shell.h"

/**
 * print_error - Prints an error message to standard error.
 * @command: the name of the command that caused the error.
 * @message: the error message to be displayed.
 */
void print_error(char *command, char *message)
{
    _puts(command);
    _puts(": ");
    _puts(message);
    _puts("\n");
}

/**
 * _puts - Writes a string to standard output.
 * @str: the string to be written.
 */
void _puts(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        _putchar(str[i]);
    }
}

/**
 * _putchar - Writes a character to standard output.
 * @c: the character to be written.
 * 
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    return (write(1, &c, 1));
}

