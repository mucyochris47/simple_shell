#include "shell.h"

/**
 * exit_shell - Terminates the shell session
 * @info: Structure containing potential arguments for the function.
 *        Maintains a consistent function prototype.
 * Return: Exits with the specified exit status.
 *         (0) if info.argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
	int exit_status;

	if (info->argv[1]) /* If an exit argument is provided */
	{
		exit_status = parse_error(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			print_str(info->argv[1]);
			print_char('\n');
			return (1);
		}
		info->err_num = parse_error(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * change_dir - Changes the current working directory
 * @info: Structure containing potential arguments for the function.
 *        Maintains a consistent function prototype.
 * Return: Always returns 0
 */
int change_dir(info_t *info)
{
	char *current_dir, *target_dir, buffer[1024];
	int change_dir_result;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		print_str("Error: Unable to get current working directory\n");

	if (!info->argv[1])
	{
		target_dir = get_env_variable(info, "HOME=");
		if (!target_dir)
			change_dir_result = chdir((target_dir = get_env_variable(info, "PWD=")) ? target_dir : "/");
		else
			change_dir_result = chdir(target_dir);
	}
	else if (string_compare(info->argv[1], "-") == 0)
	{
		if (!get_env_variable(info, "OLDPWD="))
		{
			print_str(current_dir);
			print_char('\n');
			return (1);
		}
		print_str(get_env_variable(info, "OLDPWD="));
		print_char('\n');
		change_dir_result = chdir((target_dir = get_env_variable(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		change_dir_result = chdir(info->argv[1]);

	if (change_dir_result == -1)
	{
		print_error(info, "Unable to change directory to ");
		print_str(info->argv[1]);
		print_char('\n');
	}
	else
	{
		set_env_variable(info, "OLDPWD", get_env_variable(info, "PWD="));
		set_env_variable(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * show_help - Provides help information about shell commands
 * @info: Structure containing potential arguments for the function.
 *        Maintains a consistent function prototype.
 * Return: Always returns 0
 */
int show_help(info_t *info)
{
	char **args_list;

	args_list = info->argv;
	print_str("Help functionality is active, but the implementation is incomplete.\n");
	if (0)
		print_str(*args_list); /* Placeholder to avoid unused variable warning */
	return (0);
}

