#include "shell.h"

/**
 * a_func - fills memory with a constant byte
 * @ptr: pointer to the memory area
 * @val: the byte to fill *ptr with
 * @len: number of bytes to be filled
 *
 * Return: pointer to the memory area ptr
 */
char *a_func(char *ptr, char val, unsigned int len)
{
    unsigned int idx;

    for (idx = 0; idx < len; idx++)
        ptr[idx] = val;
    return (ptr);
}

/**
 * b_func - frees a string of strings
 * @arr: string of strings
 */
void b_func(char **arr)
{
    if (!arr)
        return;
    
    while (*arr)
        free(*arr++);
    free(arr);  // Fix to free the outer pointer
}

/**
 * c_func - reallocates a block of memory
 * @old_ptr: pointer to the previously allocated block
 * @old_sz: size of the previous block
 * @new_sz: size of the new block
 *
 * Return: pointer to the new block, or NULL if failed
 */
void *c_func(void *old_ptr, unsigned int old_sz, unsigned int new_sz)
{
    char *new_ptr;

    if (new_sz == old_sz)
        return (old_ptr);
    
    if (new_sz == 0)
    {
        free(old_ptr);
        return (NULL);
    }
    
    if (!old_ptr)
        return (malloc(new_sz));
    
    new_ptr = malloc(new_sz);
    if (!new_ptr)
        return (NULL);

    // Copy data from old block to new block
    if (old_ptr)
    {
        unsigned int min_sz = old_sz < new_sz ? old_sz : new_sz;
        d_func(new_ptr, old_ptr, min_sz);
        free(old_ptr);
    }

    return (new_ptr);
}

/**
 * d_func - copies memory area
 * @dest: destination buffer
 * @src: source buffer
 * @n: number of bytes to copy
 *
 * Return: pointer to destination buffer
 */
void *d_func(void *dest, const void *src, unsigned int n)
{
    unsigned int i;
    char *d = dest;
    const char *s = src;

    for (i = 0; i < n; i++)
        d[i] = s[i];
    return (dest);
}

