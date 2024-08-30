#include "shell.h"

/**
 * show_history - shows the command history, displaying each command
 *                 with a preceding line number starting from 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        the function prototype.
 * Return: Always returns 0
 */
int show_history(info_t *info)
{
    display_list(info->history);
    return (0);
}

/**
 * remove_alias - removes an alias specified by the string
 * @info: parameter structure
 * @str: alias string
 *
 * Return: Returns 0 on success, 1 on failure
 */
int remove_alias(info_t *info, char *str)
{
    char *pos, temp_char;
    int result;

    pos = _strchr(str, '=');
    if (!pos)
        return (1);
    temp_char = *pos;
    *pos = 0;
    result = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *pos = temp_char;
    return (result);
}

/**
 * add_or_update_alias - adds a new alias or updates an existing one
 * @info: parameter structure
 * @str: alias string
 *
 * Return: Returns 0 on success, 1 on failure
 */
int add_or_update_alias(info_t *info, char *str)
{
    char *pos;

    pos = _strchr(str, '=');
    if (!pos)
        return (1);
    if (!*++pos)
        return (remove_alias(info, str));

    remove_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * display_alias - prints the alias string from a list node
 * @node: the alias node
 *
 * Return: Returns 0 on success, 1 on failure
 */
int display_alias(list_t *node)
{
    char *pos = NULL, *start = NULL;

    if (node)
    {
        pos = _strchr(node->str, '=');
        for (start = node->str; start <= pos; start++)
            _putchar(*start);
        _putchar('\'');
        _putstr(pos + 1);
        _putstr("'\n");
        return (0);
    }
    return (1);
}

/**
 * _myalias - emulates the alias builtin (refer to alias man page)
 * @info: Structure containing potential arguments. Used to maintain
 *        the function prototype.
 * Return: Always returns 0
 */
int _myalias(info_t *info)
{
    int i = 0;
    char *pos = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            display_alias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        pos = _strchr(info->argv[i], '=');
        if (pos)
            add_or_update_alias(info, info->argv[i]);
        else
            display_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}

