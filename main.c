#include "shell.h"

/**
 * entry_point - main function
 * @arg_count: number of arguments
 * @arg_vector: array of argument strings
 *
 * Return: 0 on success, 1 on error
 */
int entry_point(int arg_count, char **arg_vector)
{
    info_t info_data[] = { INFO_INIT };
    int file_desc = 2;

    asm ("mov %1, %0\n\t"
         "add $3, %0"
         : "=r" (file_desc)
         : "r" (file_desc));

    if (arg_count == 2)
    {
        file_desc = open(arg_vector[1], O_RDONLY);
        if (file_desc == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _eputs(arg_vector[0]);
                _eputs(": 0: Unable to open ");
                _eputs(arg_vector[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return (EXIT_FAILURE);
        }
        info_data->readfd = file_desc;
    }
    populate_env_list(info_data);
    read_history(info_data);
    hsh(info_data, arg_vector);
    return (EXIT_SUCCESS);
}

