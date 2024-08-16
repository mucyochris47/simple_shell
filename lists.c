#include "shell.h"

/**
 * add_node - Adds a new node to the beginning of a linked list
 * @head: Double pointer to the head of the list
 * @data: Data to store in the new node
 * Return: Pointer to the new node, or NULL on failure
 */
ListNode *add_node(ListNode **head, const char *data)
{
    ListNode *new_node;

    if (head == NULL || data == NULL)
        return (NULL);

    new_node = malloc(sizeof(ListNode));
    if (new_node == NULL)
        return (NULL);

    new_node->data = strdup(data);
    if (new_node->data == NULL)
    {
        free(new_node);
        return (NULL);
    }

    new_node->next = *head;
    *head = new_node;

    return (new_node);
}

/**
 * print_list - Prints all the nodes in a linked list
 * @head: Pointer to the head of the list
 */
void print_list(const ListNode *head)
{
    const ListNode *current;

    current = head;
    while (current != NULL)
    {
        printf("%s\n", current->data);
        current = current->next;
    }
}

/**
 * free_list - Frees the memory used by a linked list
 * @head: Pointer to the head of the list
 */
void free_list(ListNode *head)
{
    ListNode *current;
    ListNode *next;

    current = head;
    while (current != NULL)
    {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

