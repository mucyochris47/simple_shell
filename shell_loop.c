#include "shell.h"

/**
 * shell_loop - main shell loop
 * @data: the parameter & return info struct
 * @args: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(info_t *data, char **args)
{
	ssize_t result = 0;
	int built_in_result = 0;

	while (result != -1 && built_in_result != -2)
	{
		clear_info(data);
		if (interactive(data))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		result = get_input(data);
		if (result != -1)
		{
			set_info(data, args);
			built_in_result = find_builtin(data);
			if (built_in_result == -1)
				find_command(data);
		}
		else if (interactive(data))
			_putchar('\n');
		free_info(data, 0);
	}
	write_history(data);
	free_info(data, 1);
	if (!interactive(data) && data->status)
		exit(data->status);
	if (built_in_result == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (built_in_result);
}

/**
 * find_builtin - locates a builtin command
 * @data: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin(info_t *data)
{
	int index, built_in_result = -1;
	builtin_table builtins[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (index = 0; builtins[index].type; index++)
		if (_strcmp(data->argv[0], builtins[index].type) == 0)
		{
			data->line_count++;
			built_in_result = builtins[index].func(data);
			break;
		}
	return (built_in_result);
}

/**
 * find_command - locates a command in PATH
 * @data: the parameter & return info struct
 *
 * Return: void
 */
void find_command(info_t *data)
{
	char *path = NULL;
	int i, count;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (i = 0, count = 0; data->arg[i]; i++)
		if (!is_delim(data->arg[i], " \t\n"))
			count++;
	if (!count)
		return;

	path = find_path(data, _getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		execute_command(data);
	}
	else
	{
		if ((interactive(data) || _getenv(data, "PATH=")
			|| data->argv[0][0] == '/') && is_cmd(data, data->argv[0]))
			execute_command(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
 * execute_command - forks an exec thread to run cmd
 * @data: the parameter & return info struct
 *
 * Return: void
 */
void execute_command(info_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			free_info(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}

