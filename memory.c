#include "shell.h"

/**
 * allocate_memory - Allocates memory and handles allocation errors
 * @size: Size of the memory to allocate
 * Return: Pointer to the allocated memory
 */
void *allocate_memory(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/**
 * free_memory - Frees allocated memory
 * @ptr: Pointer to the memory to free
 */
void free_memory(void *ptr)
{
    free(ptr);
}

/**
 * reallocate_memory - Reallocates memory and handles allocation errors
 * @ptr: Pointer to the existing memory block
 * @old_size: Old size of the memory block
 * @new_size: New size of the memory block
 * Return: Pointer to the reallocated memory
 */
void *reallocate_memory(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr = realloc(ptr, new_size);
    if (new_ptr == NULL)
    {
        perror("realloc");
        free(ptr);  // Free old memory if realloc fails
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

