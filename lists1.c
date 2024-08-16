#include "shell.h"

/**
 * find_node - Finds a node in the linked list by its data
 * @head: Pointer to the head of the list
 * @data: Data to search for
 * Return: Pointer to the node with the matching data, or NULL if not found
 */
ListNode *find_node(const ListNode *head, const char *data)
{
    const ListNode *current = head;

    while (current != NULL)
    {
        if (strcmp(current->data, data) == 0)
            return (ListNode *)current;
        current = current->next;
    }
    return (NULL);
}

/**
 * delete_node - Deletes the first occurrence of a node with the specified data
 * @head: Double pointer to the head of the list
 * @data: Data to delete
 * Return: 1 on success, or 0 if the node was not found
 */
int delete_node(ListNode **head, const char *data)
{
    ListNode *current = *head;
    ListNode *prev = NULL;

    if (current != NULL && strcmp(current->data, data) == 0)
    {
        *head = current->next;
        free(current->data);
        free(current);
        return (1);
    }

    while (current != NULL && strcmp(current->data, data) != 0)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
        return (0);

    prev->next = current->next;
    free(current->data);
    free(current);

    return (1);
}

/**
 * length_list - Calculates the length of the linked list
 * @head: Pointer to the head of the list
 * Return: The number of nodes in the list
 */
size_t length_list(const ListNode *head)
{
    size_t length = 0;
    const ListNode *current = head;

    while (current != NULL)
    {
        length++;
        current = current->next;
    }

    return (length);
}

