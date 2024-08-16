#include "shell.h"

/**
 * safe_realloc - Reallocates memory with error checking
 * @ptr: Pointer to the existing memory block
 * @old_size: The old size of the memory block
 * @new_size: The new size of the memory block
 * Return: Pointer to the newly allocated memory block
 */
void *safe_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr;

    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }

    new_ptr = realloc(ptr, new_size);
    if (new_ptr == NULL)
    {
        perror("realloc");
        exit(EXIT_FAILURE);
    }

    return new_ptr;
}

