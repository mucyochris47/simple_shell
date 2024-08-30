#include "shell.h"

/**
 * fetch_history_file - retrieves the path to the history file
 * @data: parameter structure
 *
 * Return: dynamically allocated string containing the history file path
 */
char *fetch_history_file(data_t *data)
{
    char *path, *full_path;

    path = get_environment_variable(data, "HOME=");
    if (!path)
        return (NULL);
    full_path = malloc(sizeof(char) * (_strlen(path) + _strlen(HISTORY_FILE) + 2));
    if (!full_path)
        return (NULL);
    full_path[0] = '\0';
    _strcpy(full_path, path);
    _strcat(full_path, "/");
    _strcat(full_path, HISTORY_FILE);
    return (full_path);
}

/**
 * save_history - writes the history to a file, creating or appending as needed
 * @data: the parameter structure
 *
 * Return: 1 on success, otherwise -1
 */
int save_history(data_t *data)
{
    ssize_t file_descriptor;
    char *file_path = fetch_history_file(data);
    node_t *current_node = NULL;

    if (!file_path)
        return (-1);

    file_descriptor = open(file_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(file_path);
    if (file_descriptor == -1)
        return (-1);

    for (current_node = data->history; current_node; current_node = current_node->next)
    {
        print_to_file(current_node->str, file_descriptor);
        write_to_file('\n', file_descriptor);
    }
    write_to_file(BUFFER_FLUSH, file_descriptor);
    close(file_descriptor);
    return (1);
}

/**
 * load_history - loads history from a file
 * @data: the parameter structure
 *
 * Return: number of history lines on success, 0 otherwise
 */
int load_history(data_t *data)
{
    int index, last_pos = 0, count = 0;
    ssize_t file_descriptor, read_length, file_size = 0;
    struct stat file_stats;
    char *buffer = NULL, *file_path = fetch_history_file(data);

    if (!file_path)
        return (0);

    file_descriptor = open(file_path, O_RDONLY);
    free(file_path);
    if (file_descriptor == -1)
        return (0);

    if (!fstat(file_descriptor, &file_stats))
        file_size = file_stats.st_size;
    if (file_size < 2)
        return (0);

    buffer = malloc(sizeof(char) * (file_size + 1));
    if (!buffer)
        return (0);

    read_length = read(file_descriptor, buffer, file_size);
    buffer[file_size] = '\0';
    if (read_length <= 0)
        return (free(buffer), 0);

    close(file_descriptor);

    for (index = 0; index < file_size; index++)
        if (buffer[index] == '\n')
        {
            buffer[index] = '\0';
            append_to_history_list(data, buffer + last_pos, count++);
            last_pos = index + 1;
        }

    if (last_pos != index)
        append_to_history_list(data, buffer + last_pos, count++);

    free(buffer);
    data->history_count = count;

    while (data->history_count-- >= HISTORY_MAX)
        remove_node_at_index(&(data->history), 0);

    update_history_numbers(data);
    return (data->history_count);
}

/**
 * append_to_history_list - adds an entry to the history linked list
 * @data: structure containing arguments
 * @entry: history entry buffer
 * @line_number: line number in the history
 *
 * Return: Always 0
 */
int append_to_history_list(data_t *data, char *entry, int line_number)
{
    node_t *new_node = NULL;

    if (data->history)
        new_node = data->history;
    add_node_to_end(&new_node, entry, line_number);

    if (!data->history)
        data->history = new_node;
    return (0);
}

/**
 * update_history_numbers - updates the history line numbers
 * @data: structure containing arguments
 *
 * Return: the new history count
 */
int update_history_numbers(data_t *data)
{
    node_t *current_node = data->history;
    int count = 0;

    while (current_node)
    {
        current_node->num = count++;
        current_node = current_node->next;
    }
    return (data->history_count = count);
}

