#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <tchar.h>

#ifndef buffer_size
    #define buffer_size 1024
#endif


#ifndef SHELL_DELIMS
    #define SHELL_DELIMS " \t\r\n\a"
#endif

void shell_loop(void);
char *shell_read_line(void);
char **shell_split_line(char *line);
int shell_execute(char **args);


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


        if(c == '\n')
        {
            buffer[p] = '\0';
            
            //printf("%s \n" , buffer);

            return buffer;

        }

        else
        {

            buffer[p] = c;
           
        }

        p++;
        
        if(p>=buff_size)
        {
            buff_size += buff_size;

            buffer = realloc(buffer , buff_size);

            if(!buffer)
            {
                printf("shell memory allocation error \n");

                exit(EXIT_FAILURE);
            }
        }
        

    }
}


int shell_launch(char **args)
{
    STARTUPINFO si; //struct for startup info

    PROCESS_INFORMATION pi; //struct for process info 

    ZeroMemory(&si , sizeof(si));
    si.cb = sizeof(si);
    
    ZeroMemory(&pi , sizeof(pi));

    if(
        !CreateProcess(
            NULL ,
            args[0],
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi

        )
    )
    {
        printf("Create process failed \n");
        exit(EXIT_FAILURE);
    }

    WaitForSingleObject(pi.hProcess,INFINITE); //wait for child process to exit

    CloseHandle(pi.hProcess);

    CloseHandle(pi.hThread);

    return 1;


}

char **shell_split_line(char *line)
{   
    int buff_size = buffer_size;
    int position = 0;
    char **tokens = malloc(buff_size*sizeof(char));
    char *token;

    if(!tokens)
    {
        printf("memory allocation error \n");

        exit(EXIT_FAILURE);
    }

    token = strtok(line , SHELL_DELIMS);

    while(token != NULL)
    {
        tokens[position] = token;

        position++;

        printf("%s \n" , token);

        if(position >= buff_size )
        {

            buff_size += buffer_size;

            tokens = realloc(tokens , buff_size);

            if(!tokens)
            {
                printf("memory allocation error \n");

                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL , SHELL_DELIMS);

        
    }

    tokens[position] = NULL;

    return tokens;
}

int shell_execute(char **args)
{
    printf("launching : %s" , args[0]);

    shell_launch(args);

    return 1;
}




void shell_loop(void)
{
    char *line;
    char **args;
    int status;

    do
    {
        printf(">>  ");
        line = shell_read_line();
        args = shell_split_line(line);
        status = shell_execute(args);

        free(line);
        free(args);

    }
    while(status);
}

int main(void)
{
    shell_loop();

    return 0;
}