#include "shell.h"
size_t my_strlen(const char *str);
/**
 * signal_handler - handles signals for ctrl c
 * @signal: signal number
 * Return: nothing
 */
void signal_handler(int signal)
{
	char *prompt = "\ncisfun ";

	(void)signal;
	write(1, prompt, my_strlen(prompt));
	fflush(stdout);
}
