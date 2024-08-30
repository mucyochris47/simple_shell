#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;  // Unused parameter
	if (!path || stat(path, &st))
		return (0);

	// Check if the file is a regular file
	return (S_ISREG(st.st_mode));
}

/**
 * dup_chars - duplicates a substring of characters from the PATH string
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to a new buffer containing the substring
 */
char *dup_chars(const char *pathstr, int start, int stop)
{
	static char buf[1024];  // Static buffer to hold the substring
	int i = 0;

	if (start >= stop || stop >= sizeof(buf))
		return (NULL);

	// Copy characters from start to stop index
	for (i = 0; start < stop; start++)
	{
		if (pathstr[start] != ':')
			buf[i++] = pathstr[start];
	}
	buf[i] = '\0';  // Null-terminate the buffer
	return (buf);
}

/**
 * find_path - finds the full path of the command in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the command to find
 *
 * Return: full path of the command if found, or NULL
 */
char *find_path(info_t *info, const char *pathstr, const char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr || !cmd)
		return (NULL);

	// Check for a relative path
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		if (is_cmd(info, (char *)cmd))
			return (strdup(cmd));
	}

	// Iterate over the PATH string to find the command
	while (pathstr[i])
	{
		if (pathstr[i] == ':' || pathstr[i] == '\0')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (path && *path)
			{
				strcat(path, "/");
				strcat(path, cmd);
				if (is_cmd(info, path))
					return (path);
			}
			curr_pos = i + 1;  // Skip past the colon
		}
		i++;
	}

	// Check the last segment after the last colon
	path = dup_chars(pathstr, curr_pos, i);
	if (path && *path)
	{
		strcat(path, "/");
		strcat(path, cmd);
		if (is_cmd(info, path))
			return (path);
	}

	return (NULL);
}

