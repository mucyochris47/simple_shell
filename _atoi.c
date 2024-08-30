#include "shell.h"

/**
 * in_interactive_mode - checks if the shell is running in interactive mode
 * @info: pointer to the structure
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int in_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_separator - verifies if a character matches any in a set of delimiters
 * @ch: the character to evaluate
 * @separators: string containing the delimiter characters
 * Return: 1 if a match is found, 0 otherwise
 */
int is_separator(char ch, char *separators)
{
	while (*separators != '\0')
	{
		if (*separators == ch)
			return (1);
		separators++;
	}
	return (0);
}

/**
 * is_alpha - checks if the character is an alphabet
 * @ch: the character to check
 * Return: 1 if the character is a letter, 0 otherwise
 */
int is_alpha(int ch)
{
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

/**
 * string_to_int - converts a string of digits into an integer
 * @str: the string to be parsed
 * Return: the integer value or 0 if no valid digits are found
 */
int string_to_int(char *str)
{
	int i = 0, sign = 1;
	unsigned int num = 0;
	int has_started = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			has_started = 1;
			num = (num * 10) + (str[i] - '0');
		}
		else if (has_started)
		{
			break;
		}
		i++;
	}

	return (sign * num);
}

