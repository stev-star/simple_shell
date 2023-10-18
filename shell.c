#include "shell.h"

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
    char *directories;
    /* for if program is found in an entry */
    size_t found = 0;
    /* for malloc */
    size_t size = 0;
    size_t i = 0;
    size_t searching_i = 0;
    char *concat_path = NULL;

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
