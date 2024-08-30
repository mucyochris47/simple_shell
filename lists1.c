#include "shell.h"

/**
 * count_list - calculates the number of nodes in a linked list
 * @start_node: pointer to the first node
 *
 * Return: number of nodes in the list
 */
size_t count_list(const list_t *start_node)
{
    size_t count = 0;

    while (start_node)
    {
        start_node = start_node->next;
        count++;
    }
    return (count);
}

/**
 * convert_list_to_array - creates an array of strings from the list->str fields
 * @list_start: pointer to the first node
 *
 * Return: array of strings
 */
char **convert_list_to_array(list_t *list_start)
{
    list_t *current_node = list_start;
    size_t list_size = count_list(list_start), idx;
    char **str_array;
    char *str;

    if (!list_start || !list_size)
        return (NULL);

    str_array = malloc(sizeof(char *) * (list_size + 1));
    if (!str_array)
        return (NULL);

    for (idx = 0; current_node; current_node = current_node->next, idx++)
    {
        str = malloc(_strlen(current_node->str) + 1);
        if (!str)
        {
            for (size_t k = 0; k < idx; k++)
                free(str_array[k]);
            free(str_array);
            return (NULL);
        }

        str = _strcpy(str, current_node->str);
        str_array[idx] = str;
    }
    str_array[idx] = NULL;
    return (str_array);
}

/**
 * display_list_elements - displays all elements of a list_t linked list
 * @start_node: pointer to the first node
 *
 * Return: number of nodes in the list
 */
size_t display_list_elements(const list_t *start_node)
{
    size_t count = 0;

    while (start_node)
    {
        _puts(convert_number(start_node->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(start_node->str ? start_node->str : "(nil)");
        _putchar('\n');
        start_node = start_node->next;
        count++;
    }
    return (count);
}

/**
 * find_node_with_prefix - finds node whose string starts with a given prefix
 * @start_node: pointer to the head of the list
 * @prefix: string to match
 * @char_after_prefix: the character after the prefix to match, or -1
 *
 * Return: node with matching prefix or NULL
 */
list_t *find_node_with_prefix(list_t *start_node, char *prefix, char char_after_prefix)
{
    char *match = NULL;

    while (start_node)
    {
        match = starts_with(start_node->str, prefix);
        if (match && ((char_after_prefix == -1) || (*match == char_after_prefix)))
            return (start_node);
        start_node = start_node->next;
    }
    return (NULL);
}

/**
 * get_node_position - finds the position of a node in the list
 * @start_node: pointer to the head of the list
 * @target_node: pointer to the node to find
 *
 * Return: position of the node or -1
 */
ssize_t get_node_position(list_t *start_node, list_t *target_node)
{
    size_t position = 0;

    while (start_node)
    {
        if (start_node == target_node)
            return (position);
        start_node = start_node->next;
        position++;
    }
    return (-1);
}

