#include <stdio.h>
#include "main.h"

/**
  * _snprint - bootleg 'snprint' function for sole purpose of simple_shell
  * @file_path: buffer to store the user command and tokenize 'PATH'
  * @token: Tokenized directories in the 'PATH' environment variable
  * @command: command of the user together with the "PATH' dir
  *
  * Return: the buffer (file_path)
  */

char *_snprint(char *file_path, char *token, char *command)
{
	_strcpy(file_path, token);
	_strcat(file_path, "/");
	_strcat(file_path, command);

	return (file_path);
}
