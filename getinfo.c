#include "shell.h"

/**
 * initialize_info - sets up the info_t structure
 * @info: pointer to the structure to initialize
 */
void initialize_info(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * configure_info - sets up the info_t structure with command arguments
 * @info: pointer to the structure to configure
 * @args: argument vector
 */
void configure_info(info_t *info, char **args)
{
    int count = 0;

    info->fname = args[0];
    if (info->arg)
    {
        info->argv = split_string(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = duplicate_string(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (count = 0; info->argv && info->argv[count]; count++)
            ;
        info->argc = count;

        process_aliases(info);
        process_variables(info);
    }
}

/**
 * release_info - frees fields of the info_t structure
 * @info: pointer to the structure to release
 * @all: flag indicating if all fields should be freed
 */
void release_info(info_t *info, int all)
{
    free_array(info->argv);
    info->argv = NULL;
    info->path = NULL;
    if (all)
    {
        if (!info->cmd_buf)
            free(info->arg);
        if (info->env)
            free_list(&(info->env));
        if (info->history)
            free_list(&(info->history));
        if (info->alias)
            free_list(&(info->alias));
        free_array(info->environ);
        info->environ = NULL;
        free_pointer((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        _putchar(BUF_FLUSH);
    }
}

