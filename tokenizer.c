#include "shell.h"

/**
 * **split_text - splits a string into words using specified delimiters.
 * Repeated delimiters are ignored.
 * @text: the input string to split
 * @delimiters: string containing delimiters
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_text(char *text, char *delimiters)
{
    int index, start, end, count = 0;
    char **result;

    if (text == NULL || text[0] == '\0')
        return (NULL);
    if (delimiters == NULL)
        delimiters = " ";

    for (index = 0; text[index] != '\0'; index++)
    {
        if (!is_delim(text[index], delimiters) && (is_delim(text[index + 1], delimiters) || text[index + 1] == '\0'))
            count++;
    }

    if (count == 0)
        return (NULL);

    result = malloc((count + 1) * sizeof(char *));
    if (!result)
        return (NULL);

    for (index = 0, start = 0; count > 0; count--)
    {
        while (is_delim(text[start], delimiters))
            start++;

        end = start;
        while (!is_delim(text[end], delimiters) && text[end])
            end++;

        result[index] = malloc((end - start + 1) * sizeof(char));
        if (!result[index])
        {
            for (int i = 0; i < index; i++)
                free(result[i]);
            free(result);
            return (NULL);
        }

        for (int i = start; i < end; i++)
            result[index][i - start] = text[i];
        result[index][end - start] = '\0';

        start = end;
        index++;
    }
    result[index] = NULL;
    return (result);
}

/**
 * **split_text_by_char - splits a string into words using a single delimiter.
 * @text: the input string to split
 * @delimiter: the single delimiter character
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_text_by_char(char *text, char delimiter)
{
    int index, start, end, count = 0;
    char **result;

    if (text == NULL || text[0] == '\0')
        return (NULL);

    for (index = 0; text[index] != '\0'; index++)
    {
        if ((text[index] != delimiter && text[index + 1] == delimiter) ||
            (text[index] != delimiter && text[index + 1] == '\0') || text[index + 1] == delimiter)
            count++;
    }

    if (count == 0)
        return (NULL);

    result = malloc((count + 1) * sizeof(char *));
    if (!result)
        return (NULL);

    for (index = 0, start = 0; count > 0; count--)
    {
        while (text[start] == delimiter)
            start++;

        end = start;
        while (text[end] != delimiter && text[end] && text[end] != delimiter)
            end++;

        result[index] = malloc((end - start + 1) * sizeof(char));
        if (!result[index])
        {
            for (int i = 0; i < index; i++)
                free(result[i]);
            free(result);
            return (NULL);
        }

        for (int i = start; i < end; i++)
            result[index][i - start] = text[i];
        result[index][end - start] = '\0';

        start = end;
        index++;
    }
    result[index] = NULL;
    return (result);
}

