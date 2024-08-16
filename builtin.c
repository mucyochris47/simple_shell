#include "shell.h"

/**
 * _myexit - Exits the shell.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
    int exit_code;

    if (info->argv[1]) /* If there is an exit argument */
    {
        exit_code = _atoi(info->argv[1]);
        if (exit_code < 0)
        {
            /* Handle invalid exit code */
            info->status = 2;
            print_error(info, "Illegal number: ");
            _puts(info->argv[1]);
            _putchar('\n');
            return (1);
        }
        info->status = exit_code;
        exit(exit_code);
    }
    exit(info->status);
}

/**
 * _myenv - Prints the current environment.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
    char **env = info->env;

    while (*env)
    {
        _puts(*env);
        _putchar('\n');
        env++;
    }
    return (0);
}

/**
 * _mysetenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
    if (info->argc != 3)
    {
        _puts("Incorrect number of arguments\n");
        return (1);
    }
    if (_setenv(info->argv[1], info->argv[2], 1) == 0)
        return (0);
    return (1);
}

/**
 * _myunsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
    if (info->argc != 2)
    {
        _puts("Incorrect number of arguments\n");
        return (1);
    }
    if (_unsetenv(info->argv[1]) == 0)
        return (0);
    return (1);
}

