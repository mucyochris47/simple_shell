#include "shell.h"

/**
 * add_to_history - Adds a command to the history list
 * @history: Pointer to the history list
 * @command: Command to add to history
 * Return: 0 on success, -1 on failure
 */
int add_to_history(HistoryList *history, const char *command)
{
    HistoryNode *new_node;

    if (history == NULL || command == NULL)
        return (-1);

    new_node = malloc(sizeof(HistoryNode));
    if (new_node == NULL)
        return (-1);

    new_node->command = strdup(command);
    if (new_node->command == NULL)
    {
        free(new_node);
        return (-1);
    }

    new_node->next = history->head;
    history->head = new_node;

    return (0);
}

/**
 * print_history - Prints the command history
 * @history: Pointer to the history list
 */
void print_history(const HistoryList *history)
{
    HistoryNode *current;

    if (history == NULL)
        return;

    current = history->head;
    while (current != NULL)
    {
        printf("%s\n", current->command);
        current = current->next;
    }
}

/**
 * free_history - Frees the memory used by the history list
 * @history: Pointer to the history list
 */
void free_history(HistoryList *history)
{
    HistoryNode *current;
    HistoryNode *next;

    if (history == NULL)
        return;

    current = history->head;
    while (current != NULL)
    {
        next = current->next;
        free(current->command);
        free(current);
        current = next;
    }

    free(history);
}

