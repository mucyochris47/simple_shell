#include "shell.h"

/**
 * is_command_separator - determines if current character in buffer is a command separator
 * @info: the parameter struct
 * @buffer: the character buffer
 * @position: pointer to current position in buffer
 *
 * Return: 1 if separator, 0 otherwise
 */
int is_command_separator(info_t *info, char *buffer, size_t *position)
{
    size_t index = *position;

    if (buffer[index] == '|' && buffer[index + 1] == '|')
    {
        buffer[index] = 0;
        index++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buffer[index] == '&' && buffer[index + 1] == '&')
    {
        buffer[index] = 0;
        index++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buffer[index] == ';')
    {
        buffer[index] = 0;
        info->cmd_buf_type = CMD_CHAIN;
    }
    else
        return (0);
    *position = index;
    return (1);
}

/**
 * adjust_chain - adjusts chaining based on the last command status
 * @info: the parameter struct
 * @buffer: the character buffer
 * @position: pointer to current position in buffer
 * @start: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void adjust_chain(info_t *info, char *buffer, size_t *position, size_t start, size_t length)
{
    size_t index = *position;

    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buffer[start] = 0;
            index = length;
        }
    }
    if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buffer[start] = 0;
            index = length;
        }
    }

    *position = index;
}

/**
 * process_alias - processes aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if processed, 0 otherwise
 */
int process_alias(info_t *info)
{
    int iteration;
    list_t *alias_node;
    char *separator_pos;

    for (iteration = 0; iteration < 10; iteration++)
    {
        alias_node = node_starts_with(info->alias, info->argv[0], '=');
        if (!alias_node)
            return (0);
        free(info->argv[0]);
        separator_pos = _strchr(alias_node->str, '=');
        if (!separator_pos)
            return (0);
        separator_pos = _strdup(separator_pos + 1);
        if (!separator_pos)
            return (0);
        info->argv[0] = separator_pos;
    }
    return (1);
}

/**
 * process_vars - processes variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if processed, 0 otherwise
 */
int process_vars(info_t *info)
{
    int index = 0;
    list_t *env_node;

    for (index = 0; info->argv[index]; index++)
    {
        if (info->argv[index][0] != '$' || !info->argv[index][1])
            continue;

        if (!_strcmp(info->argv[index], "$?"))
        {
            replace_string(&(info->argv[index]),
                _strdup(convert_number(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->argv[index], "$$"))
        {
            replace_string(&(info->argv[index]),
                _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        env_node = node_starts_with(info->env, &info->argv[index][1], '=');
        if (env_node)
        {
            replace_string(&(info->argv[index]),
                _strdup(_strchr(env_node->str, '=') + 1));
            continue;
        }
        replace_string(&info->argv[index], _strdup(""));
    }
    return (0);
}

/**
 * replace_text - replaces the old string with a new one
 * @old: pointer to the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_text(char **old, char *new)
{
    free(*old);
    *old = new;
    return (1);
}

