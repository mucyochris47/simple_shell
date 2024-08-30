#include "shell.h"

/**
 * str_to_int - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */
int str_to_int(char *str)
{
    int index = 0;
    unsigned long int total = 0;

    if (*str == '+')
        str++;  /* Skipping leading '+' sign */
    for (index = 0; str[index] != '\0'; index++)
    {
        if (str[index] >= '0' && str[index] <= '9')
        {
            total *= 10;
            total += (str[index] - '0');
            if (total > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (total);
}

/**
 * report_error - outputs an error message
 * @info: the parameter & return info structure
 * @error_str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */
void report_error(info_t *info, char *error_str)
{
    print_err_str(info->fname);
    print_err_str(": ");
    print_d(info->line_count, STDERR_FILENO);
    print_err_str(": ");
    print_err_str(info->argv[0]);
    print_err_str(": ");
    print_err_str(error_str);
}

/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @number: the number
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int number, int fd)
{
    int (*output_char)(char) = write_char_fd;
    int i, count = 0;
    unsigned int abs_val, current;

    if (fd == STDERR_FILENO)
        output_char = write_err_char;
    if (number < 0)
    {
        abs_val = -number;
        output_char('-');
        count++;
    }
    else
        abs_val = number;
    current = abs_val;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (abs_val / i)
        {
            output_char('0' + current / i);
            count++;
        }
        current %= i;
    }
    output_char('0' + current);
    count++;

    return (count);
}

/**
 * number_to_str - converts number to a string in given base
 * @number: the number
 * @base: base for conversion
 * @flags: argument flags
 *
 * Return: string representation of the number
 */
char *number_to_str(long int number, int base, int flags)
{
    static char *digits;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long abs_number = number;

    if (!(flags & CONVERT_UNSIGNED) && number < 0)
    {
        abs_number = -number;
        sign = '-';
    }
    digits = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = digits[abs_number % base];
        abs_number /= base;
    } while (abs_number != 0);

    if (sign)
        *--ptr = sign;
    return (ptr);
}

/**
 * discard_comments - replaces first occurrence of '#' with '\0'
 * @str: address of the string to modify
 *
 * Return: Always 0
 */
void discard_comments(char *str)
{
    int index;

    for (index = 0; str[index] != '\0'; index++)
        if (str[index] == '#' && (!index || str[index - 1] == ' '))
        {
            str[index] = '\0';
            break;
        }
}

