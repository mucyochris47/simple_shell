#include "shell.h"

/**
 * get_user_info - Retrieves user information like username and home directory
 * @info: Structure to store user information
 * Return: 0 on success, -1 on failure
 */
int get_user_info(UserInfo *info)
{
    struct passwd *pwd;
    
    if (info == NULL)
        return (-1);

    pwd = getpwuid(getuid());
    if (pwd == NULL)
        return (-1);

    info->username = strdup(pwd->pw_name);
    info->home_directory = strdup(pwd->pw_dir);

    if (info->username == NULL || info->home_directory == NULL)
        return (-1);

    return (0);
}

/**
 * get_shell_info - Retrieves information about the current shell
 * @info: Structure to store shell information
 * Return: 0 on success, -1 on failure
 */
int get_shell_info(ShellInfo *info)
{
    char *shell_path;

    if (info == NULL)
        return (-1);

    shell_path = getenv("SHELL");
    if (shell_path == NULL)
        return (-1);

    info->shell_path = strdup(shell_path);
    if (info->shell_path == NULL)
        return (-1);

    return (0);
}

