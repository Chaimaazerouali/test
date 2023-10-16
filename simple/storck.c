#include "sheel.h"

/**
* customStrtok - Separates strings with delimiters.
* @str: Pointer to the array received from getline.
* @delimiters: Characters used to mark off the string in parts.
* Return: A pointer to the created token.
*/
char *customStrtok(char *str, char *delimiters)
{
int index;
static char *token;
char *strcopy;

if (str != NULL)
token = str;
for (; *token != '\0'; token++)
{
for (index = 0; delimiters[index] != '\0'; index++)
{
if (*token == delimiters[index])
break;
}
if (delimiters[index] == '\0')
break;
}
strcopy = token;
if (*strcopy == '\0')
return (NULL);
for (; *token != '\0'; token++)
{
for (index = 0; delimiters[index] != '\0'; index++)
{
if (*token == delimiters[index])
{
*token = '\0';
token++;
return (strcopy);
}
}
}
return (strcopy);
}

