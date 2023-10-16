#include "shell.h"

/* Function prototypes */
void prompt_user(char **line, size_t *len);
void handle_commands(char *line, char ***command, size_t *i);
void tokenize_command(char *line, char ***command, size_t *max_command, size_t *i);
void allocate_space_for_command(char ***command, size_t *max_command, size_t i);
void check_program_name(char *line, char **path);
void search_directories(char **path, char ***directories, char *line, char ***command, size_t *max_directories, size_t *searching_i, size_t *found);
void handle_fork(char *path, char **command, char **directories, size_t searching_i, char *line);
void clean_up(char **command, char **directories, char **path_env_var, char **concat_path, char **line);

/* main function */
int main(int ac, char **av)
{
    /* for prompting user */
    char *prompt = "cisfun$ ";
    ssize_t characters_read = 0;
    /* for getline() */
    char *line = NULL;
    size_t len = 0;
    /* for execve */
    char **command = NULL;
    /* for allocating space for command array */
    size_t max_command = 0;
    /* for getenv() */
    char *path_env_var = NULL;
    /* for checking if string is path */
    char *path = NULL;
    /* for allocating space for command array */
    size_t max_directories = 0;
    /* for tokenized path env variable to directories */
    char **directories = NULL;
    /* for if program is found in an entry */
    int found = 0;
    /* for malloc */
    size_t size = 0;

    (void)ac;

    /* handling signals */
    signal(SIGINT, signal_handler);

    while (1)
    {
        /* 1. prompts a user to enter a line (command) */
        prompt_user(&line, &len);

        /* 2. Handle commands */
        handle_commands(line, &command, &i);

        /* 3. tokenizes the command into smaller strings */
        tokenize_command(line, &command, &max_command, &i);

        /* 4. check if program name is a path or just a file name */
        check_program_name(line, &path);

        /* 5. Search directories */
        search_directories(&path, &directories, line, &command, &max_directories, &searching_i, &found);

        /* 6. Handle fork */
        handle_fork(path, command, directories, searching_i, line);

        /* 7. Clean up */
        clean_up(command, directories, path_env_var, concat_path, line);
    }

    return (0);
}

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
    else if (characters_read == -1)
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

void search_directories(char **path, char ***directories, char *line, char ***command, size_t *max_directories, size_t *searching_i, size_t *found)
{
    /* if program name is not a path */
    if (*path == NULL) {
        /* taking environment variable PATH */
        char *PATH = getenv("PATH");

        if (PATH == NULL)
            continue;

        /*CHECK IF STRDUP SUCCEEDED*/
        path_env_var = my_strdup(PATH);
        if (path_env_var == NULL)
            continue;

        /* tokenize PATH into array directories*/
        directories_token = strtok(path_env_var, ":");
        if (directories_token == NULL)
	{
            perror("av[0]");/*PROGRAM NAME ./hsh*/
        }

        /* allcoating space for directories array */
        *max_directories = 100;/*max_path = 4096*/
        *directories = malloc(sizeof(char *) * *max_directories);
        directories_i = 0;

        while (directories_token != NULL)
	{
            if (directories_i >= *max_directories)
	    {
                *max_directories *= 2;
                *directories = realloc(*directories, sizeof(char *) * *max_directories);
                if (*directories == NULL)
		{
                    perror("realloc");
                }
            }
            /*what if strdup fails?*/
            (*directories)[directories_i] = my_strdup(directories_token);
            if (PATH == NULL)
                continue;
            directories_token = strtok(NULL, ":");
            directories_i++;
        }
        /* null terminate directories array */
        (*directories)[directories_i] = NULL;

        /* opening all directories to look for line(e.g "ls") */
        *searching_i = 0;
        while ((*directories)[*searching_i] != NULL)
	{
            directory_stream = opendir((*directories)[*searching_i]);

            if (directory_stream == NULL)
	    {
                (*searching_i)++;
                continue;
            }

            *found = 0;
            entry = readdir(directory_stream);
            while (entry != NULL)
	    {
                if (my_strcmp(command[0], entry->d_name) == 0)
		{
                    *found = 1;
                    break;
                }

                entry = readdir(directory_stream);
            }

            closedir(directory_stream);

            if(*found)
	    {
                break;
            }
	    else
	    {
                (*searching_i)++;
            }
        }
    }
}
void handle_fork(char *path, char **command, char **directories, size_t searching_i, char *line)
{
    /* 5. forks program to create a new process (child) */
    /*check if i found executatble path use found*/
    child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork");
    }
    else if (child_pid == 0)
    {
        /* this is the child */
        if (path == NULL)/*if not a path*/
        {
            size = my_strlen(directories[searching_i]) + my_strlen(line) + 2;
            concat_path = malloc(size);
            if (concat_path == NULL)
	    {
                perror("malloc");
            }

            /* forming a path to be executed */
            my_strcpy(concat_path, directories[searching_i]);
            my_strcat(concat_path, "/");
            my_strcat(concat_path, command[0]/*line*/);

            /* executing the program */
            command[0] = concat_path;
            execve(command[0], command, environ);

            /* if execve fails */
            perror("execve");
            free(concat_path);
            free(command);
        }
        else 
	{
            (void)av;
            (void)err_msg;
            execve(command[0], command, environ);

            /* handle execve failure */
            perror("execve");
        }

    }

    /* continuing what happens in the parent (this program) */
    wait(&status);
}

void clean_up(char **command, char **directories, char **path_env_var, char **concat_path, char **line)
{
    /* freeing directories_i */
    if (path == NULL) 
    {
        for (free_dir_i = 0; directories[free_dir_i] != NULL; free_dir_i++)
	{
            free(directories[free_dir_i]);
            directories[free_dir_i] = NULL;
        }
        free(directories);
        directories = NULL;
    }

    /* freeing command[i] */
    for (i = 0; command[i] != NULL; i++) 
    {
        free(command[i]);
        command[i] = NULL;
    }
    free(command);
    command = NULL;

    free(path_env_var);
    path_env_var = NULL;

    free(concat_path);
    concat_path = NULL;

    /*end of loop;*/
    while (line != NULL)
    {
        free(line);
        line = NULL;
    }
}
