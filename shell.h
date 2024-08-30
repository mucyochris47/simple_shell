#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer sizes for read/write operations */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define FLUSH_BUFFER -1

/* Types of command chaining */
#define CHAIN_NORMAL 0
#define CHAIN_OR 1
#define CHAIN_AND 2
#define CHAIN_SEQUENTIAL 3

/* Number conversion flags */
#define CONVERT_LOWER 1
#define CONVERT_UNSIGNED 2

/* Environment variable settings */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE_NAME ".shell_history"
#define MAX_HISTORY 4096

extern char **environ;

/**
 * struct listnode - singly linked list node
 * @index: index number of the node
 * @value: a string value
 * @next: pointer to the next node
 */
typedef struct listnode
{
    int index;
    char *value;
    struct listnode *next;
} list_node;

/**
 * struct shell_info - contains information for shell operations
 * @input: input string from getline
 * @args: argument array parsed from input
 * @cmd_path: path to the command
 * @arg_count: number of arguments
 * @line_no: line number for errors
 * @error_code: error code for exit statuses
 * @flag_count: flag for line count
 * @prog_name: name of the program
 * @env_vars: linked list of environment variables
 * @env_copy: custom environment variables list
 * @history_list: history of commands
 * @alias_list: list of aliases
 * @env_modified: flag indicating if environment was modified
 * @status_code: return status of the last command
 * @cmd_buffer: command buffer for chaining
 * @buffer_type: type of command buffer
 * @input_fd: file descriptor for input
 * @history_count: number of history lines
 */
typedef struct shell_info
{
    char *input;
    char **args;
    char *cmd_path;
    int arg_count;
    unsigned int line_no;
    int error_code;
    int flag_count;
    char *prog_name;
    list_node *env_vars;
    list_node *history_list;
    list_node *alias_list;
    char **env_copy;
    int env_modified;
    int status_code;

    char **cmd_buffer; /* Pointer to command buffer for chaining */
    int buffer_type; /* Type of command buffer */
    int input_fd;
    int history_count;
} shell_info;

#define SHELL_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

/**
 * struct builtin_cmd - maps builtin commands to their functions
 * @cmd: the command string
 * @func: function associated with the command
 */
typedef struct builtin_cmd
{
    char *cmd;
    int (*func)(shell_info *);
} builtin_cmd_table;

/* shell_loop.c */
int shell_loop(shell_info *, char **);
int locate_builtin(shell_info *);
void locate_command(shell_info *);
void execute_command(shell_info *);

/* parser.c */
int is_executable(shell_info *, char *);
char *copy_chars(char *, int, int);
char *search_path(shell_info *, char *, char *);

/* shell_entry.c */
int shell_entry(char **);

/* error_handlers.c */
void print_error_message(char *);
int print_char_to_fd(char, int fd);
int print_string_to_fd(char *str, int fd);

/* string_util.c */
int string_length(char *);
int string_compare(char *, char *);
char *string_starts_with(const char *, const char *);
char *concatenate_strings(char *, char *);

/* string_util1.c */
char *copy_string(char *, char *);
char *duplicate_string(const char *);
void print_string(char *);
int print_character(char);

/* exit_handlers.c */
char *copy_n_chars(char *, char *, int);
char *concat_n_chars(char *, char *, int);
char *find_char_in_string(char *, char);

/* tokenizer.c */
char **split_string(char *, char *);
char **split_string_2(char *, char);

/* memory_management.c */
char *fill_memory(char *, char, unsigned int);
void free_string_array(char **);
void *resize_memory(void *, unsigned int, unsigned int);

/* memory_util.c */
int free_pointer(void **);

/* atoi_util.c */
int is_interactive_mode(shell_info *);
int is_delimiter(char, char *);
int is_alpha_character(int);
int string_to_int(char *);

/* error_util.c */
int string_to_int_error(char *);
void show_error(shell_info *, char *);
int print_decimal(int, int);
char *convert_to_number(long int, int, int);
void remove_comment(char *);

/* builtin_cmds.c */
int shell_exit(shell_info *);
int shell_cd(shell_info *);
int shell_help(shell_info *);

/* builtin_cmds1.c */
int shell_history(shell_info *);
int shell_alias(shell_info *);

/* getline_util.c */
ssize_t read_input(shell_info *);
int read_line(shell_info *, char **, size_t *);
void handle_sigint(int);

/* info_util.c */
void reset_info(shell_info *);
void initialize_info(shell_info *, char **);
void deallocate_info(shell_info *, int);

/* environ_util.c */
char *get_environment_variable(shell_info *, const char *);
int shell_env(shell_info *);
int shell_setenv(shell_info *);
int shell_unsetenv(shell_info *);
int populate_env_variables(shell_info *);

/* getenv_util.c */
char **retrieve_environment(shell_info *);
int unset_environment_variable(shell_info *, char *);
int set_environment_variable(shell_info *, char *, char *);

/* history_util.c */
char *retrieve_history_file(shell_info *);
int save_history(shell_info *);
int load_history(shell_info *);
int add_history_entry(shell_info *, char *, int);
int renumber_history_entries(shell_info *);

/* list_util.c */
list_node *insert_node(list_node **, const char *, int);
list_node *append_node(list_node **, const char *, int);
size_t display_list_strings(const list_node *);
int remove_node_at(list_node **, unsigned int);
void release_list(list_node **);

/* list_util1.c */
size_t get_list_length(const list_node *);
char **convert_list_to_strings(list_node *);
size_t display_list(const list_node *);
list_node *find_node_starting_with(list_node *, char *, char);
ssize_t get_node_position(list_node *, list_node *);

/* variable_util.c */
int is_command_chain(shell_info *, char *, size_t *);
void evaluate_command_chain(shell_info *, char *, size_t *, size_t, size_t);
int replace_aliases(shell_info *);
int replace_environment_variables(shell_info *);
int replace_string_in_array(char **, char *);

#endif

