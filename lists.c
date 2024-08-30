#include "shell.h"

/**
 * insert_node_at_start - inserts a node at the beginning of the list
 * @head_ref: address of pointer to the head node
 * @data: string data for the node
 * @index: index used for node identification
 *
 * Return: pointer to the new node
 */
list_t *insert_node_at_start(list_t **head_ref, const char *data, int index)
{
    list_t *new_node;

    if (!head_ref)
        return (NULL);
    
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);

    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->index = index;

    if (data)
    {
        new_node->data = _strdup(data);
        if (!new_node->data)
        {
            free(new_node);
            return (NULL);
        }
    }
    
    new_node->next = *head_ref;
    *head_ref = new_node;
    return (new_node);
}

/**
 * append_node_to_end - appends a node to the end of the list
 * @head_ref: address of pointer to the head node
 * @data: string data for the node
 * @index: index used for node identification
 *
 * Return: pointer to the new node
 */
list_t *append_node_to_end(list_t **head_ref, const char *data, int index)
{
    list_t *new_node, *current_node;

    if (!head_ref)
        return (NULL);

    current_node = *head_ref;
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);

    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->index = index;

    if (data)
    {
        new_node->data = _strdup(data);
        if (!new_node->data)
        {
            free(new_node);
            return (NULL);
        }
    }

    if (current_node)
    {
        while (current_node->next)
            current_node = current_node->next;
        current_node->next = new_node;
    }
    else
        *head_ref = new_node;
    
    return (new_node);
}

/**
 * display_list_data - displays only the data field of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t display_list_data(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        _puts(head->data ? head->data : "(nil)");
        _puts("\n");
        head = head->next;
        count++;
    }
    return (count);
}

/**
 * remove_node_by_index - removes a node at a specified index
 * @head_ref: address of pointer to the first node
 * @index: index of the node to remove
 *
 * Return: 1 on success, 0 on failure
 */
int remove_node_by_index(list_t **head_ref, unsigned int index)
{
    list_t *current_node, *previous_node;
    unsigned int i = 0;

    if (!head_ref || !*head_ref)
        return (0);

    if (index == 0)
    {
        current_node = *head_ref;
        *head_ref = (*head_ref)->next;
        free(current_node->data);
        free(current_node);
        return (1);
    }

    current_node = *head_ref;
    while (current_node)
    {
        if (i == index)
        {
            previous_node->next = current_node->next;
            free(current_node->data);
            free(current_node);
            return (1);
        }
        i++;
        previous_node = current_node;
        current_node = current_node->next;
    }
    return (0);
}

/**
 * destroy_list - deallocates all nodes of a list
 * @head_ref: address of pointer to the head node
 *
 * Return: void
 */
void destroy_list(list_t **head_ref)
{
    list_t *current_node, *next_node;

    if (!head_ref || !*head_ref)
        return;

    current_node = *head_ref;
    while (current_node)
    {
        next_node = current_node->next;
        free(current_node->data);
        free(current_node);
        current_node = next_node;
    }
    *head_ref = NULL;
}

