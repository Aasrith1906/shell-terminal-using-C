#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


#ifndef buffer_size
    #define buffer_size 1024
#endif

void shell_loop(void);
char *shell_read_line(void);
char **shell_split_line(char *line);
int shell_execute(char **args);


char **shell_split_line(char *line)
{
    char **tokens = malloc(buffer_size*sizeof(char));
    
    return tokens;
}

int shell_execute(char **args)
{
    //printf("executing lol \n");
}


char *shell_read_line(void)
{
    int buff_size = buffer_size;
    char *buffer = malloc(sizeof(char)*buff_size);
    int p = 0;
    int c;

    if(!buffer)
    {
        printf("memory allocation error! \n");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        c = getchar();


        if(c == EOF)
        {
            buffer[p] = '\0';

            printf("%s \n" , buffer);
            return buffer;

            exit(EXIT_SUCCESS);
        }

        else
        {
            if(p<=sizeof(buffer))
            {
                buffer[p] = c;
                p++;
            }
            else
            {
                buff_size += buff_size;

                buffer = realloc(buffer , buff_size);

                if(!buffer)
                {
                    printf("memory allocation error \n");
                    exit(EXIT_FAILURE);
                }
            }
            
        }
    }
}

void shell_loop(void)
{
    char *line;
    char **args;
    int status;

    do
    {
        printf(">  ");
        line = shell_read_line();

        if(line == "exit")
            status = 0;

        args = shell_split_line(line);
        status = shell_execute(args);

    }
    while(status);
}

int main(void)
{
    shell_loop();

    return 0;
}