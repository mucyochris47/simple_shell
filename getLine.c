#include "shell.h"

/**
 * buffer_input - buffers concatenated commands
 * @context: parameter struct
 * @buffer: address of buffer
 * @size: address of size variable
 *
 * Return: number of bytes read
 */
ssize_t buffer_input(info_t *context, char **buffer, size_t *size)
{
    ssize_t bytes_read = 0;
    size_t buffer_size = 0;

    if (!*size) /* if buffer is empty, fill it */
    {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, signal_handler);
#if USE_GETLINE
        bytes_read = getline(buffer, &buffer_size, stdin);
#else
        bytes_read = custom_getline(context, buffer, &buffer_size);
#endif
        if (bytes_read > 0)
        {
            if ((*buffer)[bytes_read - 1] == '\n')
            {
                (*buffer)[bytes_read - 1] = '\0'; /* remove trailing newline */
                bytes_read--;
            }
            context->linecount_flag = 1;
            remove_comments(*buffer);
            append_to_history(context, *buffer, context->histcount++);
            {
                *size = bytes_read;
                context->cmd_buf = buffer;
            }
        }
    }
    return (bytes_read);
}

/**
 * fetch_input - retrieves a line excluding the newline
 * @context: parameter struct
 *
 * Return: number of bytes read
 */
ssize_t fetch_input(info_t *context)
{
    static char *cmd_buf; /* the ';' command chain buffer */
    static size_t start_index, end_index, buf_length;
    ssize_t bytes_read = 0;
    char **cmd_ptr = &(context->arg), *cmd_start;

    _putchar(BUF_FLUSH);
    bytes_read = buffer_input(context, &cmd_buf, &buf_length);
    if (bytes_read == -1) /* EOF */
        return (-1);
    if (buf_length)    /* commands left in the buffer */
    {
        end_index = start_index; /* init iterator to current buffer position */
        cmd_start = cmd_buf + start_index; /* pointer to the command start */

        handle_chain(context, cmd_buf, &end_index, start_index, buf_length);
        while (end_index < buf_length) /* iterate to the next delimiter */
        {
            if (is_chain(context, cmd_buf, &end_index))
                break;
            end_index++;
        }

        start_index = end_index + 1; /* move past the delimiter */
        if (start_index >= buf_length) /* end of buffer reached? */
        {
            start_index = buf_length = 0; /* reset buffer state */
            context->cmd_buf_type = CMD_NORMAL;
        }

        *cmd_ptr = cmd_start; /* return pointer to current command */
        return (_strlen(cmd_start)); /* length of current command */
    }

    *cmd_ptr = cmd_buf; /* not a chain, return buffer from _getline() */
    return (bytes_read); /* length of buffer from _getline() */
}

/**
 * read_buffer - reads from a buffer
 * @context: parameter struct
 * @buf: buffer
 * @index: size
 *
 * Return: number of bytes read
 */
ssize_t read_buffer(info_t *context, char *buf, size_t *index)
{
    ssize_t bytes_read = 0;

    if (*index)
        return (0);
    bytes_read = read(context->readfd, buf, READ_BUF_SIZE);
    if (bytes_read >= 0)
        *index = bytes_read;
    return (bytes_read);
}

/**
 * custom_getline - retrieves the next line of input from STDIN
 * @context: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated buffer if not NULL
 *
 * Return: number of bytes read
 */
int custom_getline(info_t *context, char **ptr, size_t *length)
{
    static char buffer[READ_BUF_SIZE];
    static size_t buf_index, buf_len;
    size_t copy_len;
    ssize_t bytes_read = 0, total_len = 0;
    char *temp_ptr = NULL, *new_ptr = NULL, *newline;

    temp_ptr = *ptr;
    if (temp_ptr && length)
        total_len = *length;
    if (buf_index == buf_len)
        buf_index = buf_len = 0;

    bytes_read = read_buffer(context, buffer, &buf_len);
    if (bytes_read == -1 || (bytes_read == 0 && buf_len == 0))
        return (-1);

    newline = find_char(buffer + buf_index, '\n');
    copy_len = newline ? 1 + (unsigned int)(newline - buffer) : buf_len;
    new_ptr = _realloc(temp_ptr, total_len, total_len ? total_len + copy_len : copy_len + 1);
    if (!new_ptr) /* Memory allocation failure */
        return (temp_ptr ? free(temp_ptr), -1 : -1);

    if (total_len)
        concat_str(new_ptr, buffer + buf_index, copy_len - buf_index);
    else
        copy_str(new_ptr, buffer + buf_index, copy_len - buf_index + 1);

    total_len += copy_len - buf_index;
    buf_index = copy_len;
    temp_ptr = new_ptr;

    if (length)
        *length = total_len;
    *ptr = temp_ptr;
    return (total_len);
}

/**
 * signal_handler - handles SIGINT (Ctrl-C)
 * @sig_num: the signal number
 *
 * Return: void
 */
void signal_handler(__attribute__((unused))int sig_num)
{
    _putchar('\n');
    _putchar('$');
    _putchar(' ');
    _putchar(BUF_FLUSH);
}

