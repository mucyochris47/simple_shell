#include "shell.h"

/**
 * _getline - Reads a line from stdin
 * @buffer: Buffer to store the read line
 * @size: Size of the buffer
 * @stream: Input stream to read from
 * Return: Number of characters read (excluding the null terminator), or -1 on error
 */
ssize_t _getline(char **buffer, size_t *size, FILE *stream)
{
    ssize_t len;
    size_t bufsize = *size;
    char *temp_buffer;

    if (buffer == NULL || size == NULL || stream == NULL)
        return (-1);

    if (*buffer == NULL)
    {
        bufsize = 120;  /* Default buffer size */
        *buffer = malloc(bufsize);
        if (*buffer == NULL)
            return (-1);
    }

    len = getline(buffer, &bufsize, stream);
    if (len == -1)
    {
        if (feof(stream))
            return (-1);  /* End of file */
        else
            return (-1);  /* Error occurred */
    }

    /* Resize buffer if needed */
    if (len > (ssize_t)bufsize)
    {
        temp_buffer = realloc(*buffer, len + 1);
        if (temp_buffer == NULL)
            return (-1);
        *buffer = temp_buffer;
    }

    return (len);
}

