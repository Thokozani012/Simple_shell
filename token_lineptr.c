#include <stdio.h>
#include "main.h"

/**
  * token_lineptr - Tokenize the input command
  * @lineptr: command from the stdin entered by the user
  *
  * Return: On success 1 is returned, or -1 on errno.
  */

char **token_lineptr(char *lineptr)
{
	char *delimiter = " ", *token, *copy_lineptr, **args;
	int i = 0, wordCount = 0;

	copy_lineptr = _strdup(lineptr);
	if (copy_lineptr == NULL)
	{
		perror("tsh: failed to strdup 'lineptr'\n"), exit(1);
	}

	token = _strtok(copy_lineptr, delimiter);
	while (token != NULL)
	{
		wordCount++;
		token = _strtok(NULL, delimiter);
	}

	args = malloc(sizeof(char *) * (wordCount + 1));
	if (args == NULL)
	{
		perror("tsh: memory allocation failed: args\n"), exit(1);
	}

	_strcpy(copy_lineptr, lineptr);
	token = _strtok(copy_lineptr, delimiter);

	while (token != NULL)
	{
		args[i] = _strdup(token);
		if (args[i] == NULL)
		{
			perror("tsh: memory allocation failed: args[i]\n"), exit(1);
		}
		token = _strtok(NULL, delimiter);
		i++;
	}
	args[i] = NULL;

	free(copy_lineptr);
	return (args);
}
