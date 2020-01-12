#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#ifndef buffer_size
    #define buffer_size 1024
#endif

#ifndef SHELL_DELIMS
    #define SHELL_DELIMS " \t\r\n\a"
#endif

extern int (*builtin_func[]) (char**);
extern char *builtin_str[];

void shell_loop(void);
char *shell_read_line(void);
char **shell_split_line(char *line);
int shell_execute(char **args);

int shell_cd(char **args);
int shell_exit(char **args);
int shell_help(char **args);
int shell_clear_screen(char **args);
int shell_ls(char **args);
int shell_mkdir(char **args);

int num_builtin_func();