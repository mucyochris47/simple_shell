#include "shell.h"

/**
 * retrieve_environment - returns a string array copy of the environment
 * @context: Structure containing potential arguments. Used to maintain
 *           constant function prototype.
 * Return: Pointer to the environment string array
 */
char **retrieve_environment(info_t *context)
{
    if (!context->environ || context->env_modified)
    {
        context->environ = convert_list_to_strings(context->env);
        context->env_modified = 0;
    }

    return (context->environ);
}

/**
 * remove_environment - Remove an environment variable
 * @context: Structure containing potential arguments. Used to maintain
 *           constant function prototype.
 * @var: The environment variable to remove
 * Return: 1 if deleted, 0 otherwise
 */
int remove_environment(info_t *context, char *var)
{
    list_t *node = context->env;
    size_t index = 0;
    char *match;

    if (!node || !var)
        return (0);

    while (node)
    {
        match = starts_with(node->str, var);
        if (match && *match == '=')
        {
            context->env_modified = delete_node_at_index(&(context->env), index);
            index = 0;
            node = context->env;
            continue;
        }
        node = node->next;
        index++;
    }
    return (context->env_modified);
}

/**
 * create_environment - Initialize a new environment variable,
 *                       or modify an existing one
 * @context: Structure containing potential arguments. Used to maintain
 *           constant function prototype.
 * @var: The environment variable to set
 * @value: The value for the environment variable
 * Return: Always 0
 */
int create_environment(info_t *context, char *var, char *value)
{
    char *entry = NULL;
    list_t *node;
    char *match;

    if (!var || !value)
        return (0);

    entry = malloc(_strlen(var) + _strlen(value) + 2);
    if (!entry)
        return (1);
    _strcpy(entry, var);
    _strcat(entry, "=");
    _strcat(entry, value);
    node = context->env;
    while (node)
    {
        match = starts_with(node->str, var);
        if (match && *match == '=')
        {
            free(node->str);
            node->str = entry;
            context->env_modified = 1;
            return (0);
        }
        node = node->next;
    }
    append_node_end(&(context->env), entry, 0);
    free(entry);
    context->env_modified = 1;
    return (0);
}

