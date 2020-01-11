/*
    written by Aasrith Ch .
    A simple command line shell written using C can start processes , and has some basic shell commands
*/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <tchar.h>
#include <direct.h>

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

int shell_cd(char **args);
int shell_exit(char **args);
int shell_help(char **args);
int shell_clear_screen(char **args);
int num_builtin_func();



char *builtin_str[] = 
{
    "cd",
    "exit",
    "help"
    "clrscr"
};

int (*builtin_func[]) (char**) = 
{
    &shell_cd,
    &shell_exit,
    &shell_help,
    &shell_clear_screen
};

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


//shell builtins 

int shell_cd(char **args)
{
    if(args[1] == NULL)
    {
        printf("usage : cd <dir name> \n");

        return 1;
    }

    if(_chdir(args[1])==-1)
    {
        printf("error while changing directory \n");

        return 1;
    }

    return 1;
}

int shell_exit(char **args)
{
    exit(EXIT_SUCCESS);
}

int shell_help(char **args)
{
    printf(" -> COMMAND LINE SHELL CREATED BY AASRITH CH \n");
    
    printf(" -> builtin functions : \n");

    for(int i = 0 ; i < num_builtin_func(); i++)
    {
        printf("%d)%s \n",(i+1),builtin_str[i]);
    }

    return 1;
}




// end of shell builtins

int shell_launch(char **args)
{

    /* make this better */

    char *buffer;
    buffer = malloc(4*buffer_size*sizeof(char));

    buffer[0] = '\0';

    for(int i = 0; i <=sizeof(args); i++)
    {
        if(args[i] != NULL)
        {
            strcat(buffer , args[i]);
            strcat(buffer , " ");
        }    
    }

    /* make above code better (memory allocation use a int to iterate through)*/

   // printf("%s \n" , buffer);

    STARTUPINFO si; //struct for startup info

    PROCESS_INFORMATION pi; //struct for process info 

    ZeroMemory(&si , sizeof(si));
    si.cb = sizeof(si);
    
    ZeroMemory(&pi , sizeof(pi));

    if(
        !CreateProcess(
            NULL ,
            buffer,
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
        free(buffer);
        return 1;
    }

    WaitForSingleObject(pi.hProcess,INFINITE); //wait for child process to exit

    CloseHandle(pi.hProcess);

    CloseHandle(pi.hThread);

    free(buffer);

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

        //printf("%s \n" , token);

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

int num_builtin_func()
{
    return sizeof(builtin_str)/sizeof(char *);
}

int shell_execute(char **args)
{

    int i;

    int command_found_in_builtin = 0;

    if(args[0] == NULL) //empty command
    {
        return 1;
    } 

    for(i = 0; i<=num_builtin_func(); i++)
    {
        if(strcmp(args[0] , builtin_str[i]) == 0)
        {   
            command_found_in_builtin = 1;
            return (*builtin_func[i])(args);

        }
    }

    if(command_found_in_builtin == 0)
    {
        //printf("launching : %s \n" , args[0]);

         return shell_launch(args);
    }
 

   
}


void shell_loop(void)
{
    char *line;
    char **args;
    int status;

    char *directory;

    while(1)
    {
        if((directory = _getcwd(NULL , 0)) == NULL)
        {
            printf("_getcwd error \n");
            exit(EXIT_FAILURE);
        }

        printf("%s >>  " , directory);
        line = shell_read_line();
        args = shell_split_line(line);
        status = shell_execute(args);

        if(status==0)
        {
            exit(EXIT_FAILURE);
        }

        free(line);
        free(args);
        free(directory);

        printf("\n");
    }
   
}

int main(void)
{

    settext

    shell_loop();

    return 0;
}