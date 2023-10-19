#include "shell.h"

int my_strcmp(const char *string1, const char *string2);
void signal_handler(int signal);
size_t my_strlen(const char *str);
char *my_strdup(const char *str);
char *my_strcat(char *final_str, char *str_to);
char *my_strcpy(char *dest, char *src);
ssize_t my_getline(char **line, size_t *len, FILE *stream);

/**
 * split_command: Tokenizes the command into smaller strings.
 * @command: The command to be tokenized.
 * @delimiters: The delimiters to use when tokenizing the command.
 * @tokens: An array of pointers to the tokenized strings.
 * @max_tokens: The maximum number of tokens.
 *
 * Returns: The number of tokens in the command.
 */
int split_command(const char *command, const char *delimiters, char **tokens, size_t max_tokens)
{
	int i = 0;
	char *token = strtok((char *)command, delimiters);

	while (token != NULL && (size_t)i < max_tokens)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, delimiters);
	}
	tokens[i] = NULL;
	return (i);
}

/**
 * find_executable: Finds the executable file for the given command.
 * @command: The command to find the executable for.
 * @path: The path to search for the executable file.
 *
 * Returns: A pointer to the executable file, or NULL if it cannot be found.
 */
char *find_executable(const char *command, const char *path)
{
	char *full_path = malloc(strlen(path) + strlen(command) + 2);

	if (full_path == NULL)

		return (NULL);


	strcpy(full_path, path);
	strcat(full_path, "/");
	strcat(full_path, command);

	if (access(full_path, X_OK) == 0)
		return (full_path);
	else
	{
		free(full_path);
	}
	return (NULL);
}

/**
 * execute_command: Executes the given command.
 * @command: The command to execute.
 * @tokens: An array of pointers to the tokenized strings.
 *
 * Returns: The exit status of the command.
 */
int execute_command(const char *command, char **tokens)
{
	int pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		/* This is the child process. */
		execve(command, tokens, environ);
		perror("execve");
		exit(1);
	}
	else
	{
		/* This is the parent process. */
		int status;

		wait(&status);
		return (status);
	}
}
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t characters_read;
	char **tokens;
	char *executable_path;
	int status;

	/* Handling signals. */
	signal(SIGINT, signal_handler);

	while (1)
	{
		/* Prompt the user for a command. */
		write(1, "cisfun$ ", 10);
		fflush(stdout);

		/* Get the command from the user. */
		characters_read = my_getline(&line, &len, stdin);
		if (characters_read == EOF)
		{
			break;
		}
		else if (characters_read == -1)
		{
			break;
		}

		/* If the command is empty, skip it. */
		if (line == NULL || line[0] == '\0')
			continue;

		/* Split the command into tokens. */
		tokens = malloc(sizeof(char *) * 10);
		split_command(line, " ", tokens, 10);

		/* If the command is "exit", exit the program. */
		if (strcmp(tokens[0], "exit") == 0)
		{
			free(line);
			free(tokens);
			exit(0);
		}
		/* Find the executable file for the command. */
		executable_path = find_executable(tokens[0], getenv("PATH"));
		if (executable_path == NULL)
		{
			perror("Command not found");
			free(line);
			free(tokens);
			continue;
		}

		/* Execute the command. */
		status = execute_command(executable_path, tokens);

		/* Free the memory allocated for the command and executable path. */
		free(line);
		free(tokens);
		free(executable_path);

		/* Check the exit status of the command. */
		if (status != 0)
			perror("Command failed");
	}

	return (0);
}
