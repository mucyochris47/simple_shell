#include "shell.h"

/**
 * safe_free - frees a pointer and sets the address to NULL
 * @pointer: address of the pointer to be freed
 *
 * Return: 1 if the memory was freed, otherwise 0
 */
int safe_free(void **pointer)
{
    if (pointer && *pointer)
    {
        free(*pointer);
        *pointer = NULL;
        return (1);
    }
    return (0);
}

