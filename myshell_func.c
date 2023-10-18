#include "shell.h"

/* Function definitions */
void prompt_user(char **line, size_t *len)
{
    /* for prompting user */
    char *prompt = "cisfun$ ";
    ssize_t prompt_bytes_written = 0;

    if (isatty(STDIN_FILENO))
    {
        prompt_bytes_written = write(1, prompt, my_strlen(prompt));
        if (prompt_bytes_written == -1)
        {
            perror("write");
            exit(1);
        }
    }

    fflush(stdout);

    /** get command from user */
    ssize_t characters_read = my_getline(line, len, stdin);
    if (characters_read == EOF)
    {
        exit(0);
    }
}

void handle_commands(char *line, char ***command, size_t *i)
{
    /* if command is exit */
    if (my_strcmp(line, "exit") == 0)
    {
        free(line);
        exit(0);
    }

    /* if command is env */
    if (my_strcmp(line, "env") == 0)
    {
        int i = 0;

        for (; environ[i]; i++)
        {
            /*print each environment variable*/
            write(1, environ[i], my_strlen(environ[i]));
            write(1, "\n", 1);
        }
        free(line);
    }
}
void tokenize_command(char *line, char ***command, size_t *max_command, size_t *i)
{
    /* 3. tokenizes the command into smaller strings */
   /**
     * 4. smaller strings will represent the arguments
     * parameter of execve function
     */
    const char *delimiters = " \n\t\r\a";
    char *command_token = strtok(line, delimiters);
    if (command_token == NULL)
    {
        free(line);
        return;
    }

    /* allocating space for command array */
    *max_command = 10;
    *command = malloc(sizeof(char *) * *max_command);
    *i = 0;

    /* tokenize the line and put each token into the command array */
    while (command_token != NULL)
    {
        if (*i >= *max_command)
        {
            *max_command *= 2;
            *command = realloc(*command, sizeof(char *) * *max_command);
            if (*command == NULL)
            {
                perror("realloc");
                return;
            }
 }

        /* copy the token into the command array */
        (*command)[*i] = strdup(command_token);
        if ((*command)[*i] == NULL)
        {
            perror("strdup");
            return;
        }

        /* get the next token */
        command_token = strtok(NULL, delimiters);
        (*i)++;
    }

    /* null terminate the command array */
    (*command)[*i] = NULL;
}
void allocate_space_for_command(char ***command, size_t *max_command, size_t i)
{
    /* allocating space for command array */
    *max_command = 10;
    *command = malloc(sizeof(char *) * *max_command);
    i = 0;
    while (command_token != NULL)
    {
        /* reallocate memory when max commands reach */
        if (i >= *max_command)
        {
 {
            *max_command *= 2;
            *command = realloc(*command, sizeof(char *) * *max_command);
            if (*command == NULL)
            {
                perror("./hsh");
            }
        }

        /* put tokens into command array */
        (*command)[i] = my_strdup(command_token);
        if ((*command)[i] == NULL)
            continue;
        command_token = strtok(NULL, delimiters);
        i++;
    }
    /* set last element of command array to NULL */
    (*command)[i] = NULL;
}

void check_program_name(char *line, char **path)
{
    /* check if program name is a path or just a file name */
    int slash_i = 0;
    while (line[slash_i] != '\0')
    {
        if (line[slash_i] == '/')
        {
            *path = line;
           break;
        }
        slash_i++;
    }
}
