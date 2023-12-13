#include "main.h"

char *_getenv(const char *name)
{
	char **env = environ;
	int i = 0, j = 0;

	if (name == NULL)
	{
		perror("Error: argument not provided\n");
		return (NULL);
	}

	while (env[i] != NULL)
	{
		while (env[i][j] == name[j] && env[i][j] != '\0')
		{
			j++;
		}

		if (env[i][j] == '=' && name[j] == '\0')
		{
			return (&env[i][j + 1]);
		}
		j = 0;
		i++;
	}

	return (NULL);
}
