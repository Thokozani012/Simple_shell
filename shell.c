#include <stdio.h>
#include "main.h"

/**
  * _malloc_args_err - error handling for argument memory allocation
  * @args: arguments
  *
  * Return: Always -1.
  */
int _malloc_args_err(char **args)
{
	if (args ==  NULL)
	{
		perror("memory allocation failed\n");
	}
	return (-1);
}

/**
  * execute_command - executes built-in commands
  * @args: commands and arguments entered by the user
  *
  * Return: Nothing (void function)
  */
int execute_command(char **args)
{
	int i;

	static const CommandMapping commands[] = {
		{"exit", exit_builtin},
		{"env", built_in_env},
		{"./shell", _shell_in_shell},
		{"./hsh", _shell_in_shell},
		{"setenv", built_in_setenv},
		{"unsetenv", built_in_unsetenv},
		{NULL, NULL}
	};

	for (i = 0; commands[i].command != NULL; ++i)
	{
		if (_strcmp(args[0], commands[i].command) == 0)
		{
			commands[i].function(args);
			return (1); /* command was a built-in command*/
		}
	}

	return (0); /* no a built_in command*/
}

/**
 * main - command line UNIX interpreter, simple_shell
 * @argc: Argument counter
 * @argv: Argument vector
 *
 * Return: On success 0, or -1 on error/failure
 */

int main(int argc, char *argv[])
{
	ssize_t nread;
	size_t len = 0;
	char *lineptr = NULL, **args;
	int i;

	if (isatty(STDIN_FILENO))
	{
		while (1) /* interactive mode */
		{
			command_prompt();
			nread = _get(&lineptr, &len, stdin);
			if (nread == -1)
			{
				perror("\nexit\n\n\n[Disconnected...]\n");
				return (-1);
			}
			else if (nread == 1)
				continue;
			if (nread > 0 && lineptr[nread - 1] == '\n')
				lineptr[nread - 1] = '\0';
			args = token_lineptr(lineptr);
			if (!execute_command(args))
			{
				exec_with_path(args[0], args);
			}
		}
		free(lineptr);
	}
	else /*Non-interactive mode*/
	{
		args = malloc((argc - 1) * sizeof(char *));
		_malloc_args_err(args);
		for (i = 1; i < argc; i++)
			args[i - 1] = argv[i];
		args[i - 1] = NULL;
		_execvecmd(args);
	}
	return (0);
}
