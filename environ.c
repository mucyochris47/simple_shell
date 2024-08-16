#include "shell.h"

extern char **environ;

/**
 * _getenv - retrieves an environment variable.
 * @name: name of the environment variable to retrieve.
 * 
 * Return: a pointer to the value of the environment variable,
 *         or NULL if not found.
 */
char *_getenv(const char *name)
{
    size_t len = _strlen(name);

    for (int i = 0; environ[i]; i++)
    {
        if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
            return (environ[i] + len + 1);
    }
    return (NULL);
}

