#include "shell.h"

/**
 * show_environment - prints the current environment variables
 * @info: Structure containing potential arguments. Used to maintain
 *        the function prototype.
 * Return: Always returns 0
 */
int show_environment(info_t *info)
{
    print_list_str(info->env);
    return (0);
}

/**
 * find_env_value - retrieves the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @key: the environment variable name
 *
 * Return: the value of the environment variable
 */
char *find_env_value(info_t *info, const char *key)
{
    list_t *node = info->env;
    char *value;

    while (node)
    {
        value = starts_with(node->str, key);
        if (value && *value)
            return (value);
        node = node->next;
    }
    return (NULL);
}

/**
 * initialize_env - Sets a new environment variable or updates an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        the function prototype.
 * Return: Always returns 0 on success, 1 on failure
 */
int initialize_env(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Invalid number of arguments\n");
        return (1);
    }
    if (add_or_update_env(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * remove_env - Deletes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        the function prototype.
 * Return: Always returns 0
 */
int remove_env(info_t *info)
{
    int i;

    if (info->argc < 2)
    {
        _eputs("Insufficient arguments.\n");
        return (1);
    }
    for (i = 1; i < info->argc; i++)
        delete_env_var(info, info->argv[i]);

    return (0);
}

/**
 * build_env_list - creates a linked list of environment variables
 * @info: Structure containing potential arguments. Used to maintain
 *        the function prototype.
 * Return: Always returns 0
 */
int build_env_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->env = node;
    return (0);
}

