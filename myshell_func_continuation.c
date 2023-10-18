#include "shell.h"

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

            /* forming a path to be executed */            my_strcpy(concat_path, directories[searching_i]);
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
        int i = 0;
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
    for (; command[i] != NULL; i++)
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
