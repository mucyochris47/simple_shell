#include "shell.h"
#include <stdlib.h>
#include <string.h>

/**
 * get_env_var - Gets the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *get_env_var(const char *name)
{
    extern char **environ;
    char **env = environ;
    size_t name_len = strlen(name);

    while (*env)
    {
        if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
        {
            return *env + name_len + 1;
        }
        env++;
    }

    return NULL;
}

/**
 * set_env_var - Sets or updates an environment variable.
 * @name: The name of the environment variable.
 * @value: The value of the environment variable.
 * @overwrite: If non-zero, overwrite an existing variable.
 *
 * Return: 0 on success, -1 on failure.
 */
int set_env_var(const char *name, const char *value, int overwrite)
{
    extern char **environ;
    char **env = environ;
    size_t name_len = strlen(name);
    size_t value_len = strlen(value);
    size_t new_len = name_len + value_len + 2; // +2 for '=' and '\0'
    char *new_env_var;
    
    while (*env)
    {
        if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
        {
            if (overwrite)
            {
                new_env_var = malloc(new_len);
                if (new_env_var == NULL)
                {
                    perror("malloc");
                    return -1;
                }
                snprintf(new_env_var, new_len, "%s=%s", name, value);
                *env = new_env_var;
                return 0;
            }
            return 0; // Do nothing if not overwriting
        }
        env++;
    }

    // Variable not found, add it
    new_env_var = malloc(new_len);
    if (new_env_var == NULL)
    {
        perror("malloc");
        return -1;
    }
    snprintf(new_env_var, new_len, "%s=%s", name, value);
    // Append new variable to environ
    if (environ_add(new_env_var) != 0)
    {
        free(new_env_var);
        return -1;
    }

    return 0;
}

/**
 * environ_add - Adds a new environment variable to environ.
 * @new_env_var: The new environment variable to add.
 *
 * Return: 0 on success, -1 on failure.
 */
int environ_add(const char *new_env_var)
{
    extern char **environ;
    size_t i = 0;
    char **new_environ;
    
    // Find the number of environment variables
    while (environ[i])
        i++;
    
    new_environ = realloc(environ, sizeof(char *) * (i + 2));
    if (new_environ == NULL)
    {
        perror("realloc");
        return -1;
    }

    new_environ[i] = strdup(new_env_var);
    if (new_environ[i] == NULL)
    {
        perror("strdup");
        return -1;
    }
    new_environ[i + 1] = NULL;
    
    environ = new_environ;
    
    return 0;
}

/**
 * unset_env_var - Unsets an environment variable.
 * @name: The name of the environment variable to unset.
 *
 * Return: 0 on success, -1 on failure.
 */
int unset_env_var(const char *name)
{
    extern char **environ;
    char **env = environ;
    char **new_environ;
    size_t i = 0;
    size_t j = 0;
    
    // Find the number of environment variables
    while (env[i])
        i++;
    
    new_environ = malloc(sizeof(char *) * i);
    if (new_environ == NULL)
    {
        perror("malloc");
        return -1;
    }
    
    // Copy variables except the one to be removed
    env = environ;
    while (*env)
    {
        if (strncmp(*env, name, strlen(name)) != 0 || (*env)[strlen(name)] != '=')
        {
            new_environ[j++] = *env;
        }
        env++;
    }
    
    new_environ[j] = NULL;
    
    // Free the old environment and set the new one
    free(environ);
    environ = new_environ;
    
    return 0;
}

