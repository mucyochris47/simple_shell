#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function prototypes */
void *safe_realloc(void *ptr, size_t old_size, size_t new_size);
char *getenv(const char *name);
int setenv(const char *name, const char *value, int overwrite);
int unsetenv(const char *name);
void print_env(void);
void execute_command(char *command);
void handle_signal(int signal);
char **parse_command(char *command);
void free_array(char **array);
int built_in_commands(char **argv);
void prompt(void);

#endif /* SHELL_H */

