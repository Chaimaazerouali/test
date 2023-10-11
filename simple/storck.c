#include "shell.h"

/**
 * customStrtok - Separates strings with delimiters.
 * @line: Pointer to the array received from getline.
 * @delim: Characters used to mark off the string in parts.
 * Return: A pointer to the created token.
 */
char *customStrtok(char *line, char *delim)
{
	int index;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (index = 0; delim[index] != '\0'; index++)
		{
			if (*str == delim[index])
				break;
		}
		if (delim[index] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (index = 0; delim[index] != '\0'; index++)
		{
			if (*str == delim[index])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}

