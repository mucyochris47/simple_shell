#include "shell.h"

/**
 * _getenv - Retrieves the value of an environment variable
 * @name: Name of the environment variable to retrieve
 * Return: Value of the environment variable or NULL if not found
 */
char *_getenv(const char *name)
{
    extern char **environ;
    char *env;
    size_t name_len = strlen(name);

    if (name == NULL || name_len == 0)
        return (NULL);

    for (int i = 0; environ[i] != NULL; i++)
    {
        env = environ[i];
        if (strncmp(env, name, name_len) == 0 && env[name_len] == '=')
            return (env + name_len + 1);  /* Return value after '=' */
    }

    return (NULL);  /* Environment variable not found */
}

