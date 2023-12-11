#include <stdio.h>
#include "main.h"

/**
  * _found - executes the command if it exits/found
  * @file_path: file path (though 'PATH')
  * @command: command to be executed
  * @args: command arguments
  * @found: flag used to indicate when 'command' is found
  *
  * Return: Nothing (void function)
  */
int _found(char *file_path, char *command, char **args, int found)
{
	int status;
	pid_t child_pid;
	char **env = environ;

	if (found)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("tsh: fork failed: child_pid\n");
			return (-1);
		}
		else if (child_pid == 0)
		{
			if (execve(file_path, args, env) == -1)
			{
				perror("tsh: execve failed: child_pid\n");
				return (-1);
			}
		}
		else
		{
			do {
				waitpid(child_pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
	else
	{
		_fprintf(stderr, "%s: command not found\n", command);
		return (-1);
	}
	return (0);

}

/**
  * _path_err - error handlinng for the environment varable 'PATH'
  * @path: environment variable
  *
  * Return: Always -1.
  */
int _path_err(char *path)
{
	if (path == NULL)
	{
		perror("tsh:failed to get environment variable 'PATH'\n");
	}
	return (-1);
}

/**
  * _file_path_err - error handling for file_path malloc operation
  * @file_path: command path.
  *
  * Return: Always -1.
  */
int _file_path_err(char *file_path)
{
	if (file_path == NULL)
	{
		perror("memory allocation failed: args\n");
	}
	return (-1);
}
/**
  * exec_with_path - search for executeable in each dir in 'PATH'
  * @command: command to be executed
  * @args: command arguments
  *
  *
  * Return: 0 On success, or -1 on error.
  */

int exec_with_path(char *command, char **args)
{
	char *path, *path_copy, *file_path, *token;
	int found = 0;
	size_t path_len, command_len, buffer_size;

	path = getenv("PATH");
	_path_err(path);
	path_copy = _strdup(path);
	if (path_copy == NULL)
	{
		perror("tsh: memory allocation failed: copy_path\n");
		return (-1);
	}
	token = _strtok(path_copy, ":");
	while (token != NULL)
	{
		path_len = _strlen(token);
		command_len = _strlen(command);
		buffer_size = path_len + 1 + command_len + 1;

		file_path = malloc(buffer_size);
		_file_path_err(file_path);
		_snprint(file_path, token, command);
		if (access(file_path, X_OK) == 0)
		{
			found = 1;
			break;
		}
		free(file_path);
		token = _strtok(NULL, ":");
	}
	free(path_copy);
	_found(file_path, command, args, found);
	return (found ? 0 : -1);
}
