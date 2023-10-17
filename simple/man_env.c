#include "sheel.h"

/**
* getEnvironmentVariable - Get the value of an environment variable.
* @key: The name of the environment variable of interest.
* @shellData: Pointer to the custom shell data structure.
* Return: A pointer to the value of the variable, or NULL if it doesn't exist.
*/
char *getEnvironmentVariable(char *key, CustomShellData *shellData)
{
int i, keyL = 0;

/* Validate the input arguments */
if (key == NULL || shellData->env == NULL)
return (NULL);

/* Determine the length of the variable name */
keyL = strLength(key);

for (i = 0; shellData->env[i]; i++)
{
/* Iterate through the environment and check for a match */
if (strCompare(key, shellData->env[i], keyL) &&
shellData->env[i][keyL] == '=')
{
/* Return the value of the key in the format "NAME=value" */
return (shellData->env[i] + keyL + 1);
}
}
/* Return NULL if the variable was not found */
return (NULL);
}

/**
* setenvironmentVariable - Overwrite the value of an environment variable
* or create it if it does not exist.
* @key: Name of the variable to set.
* @value: New value.
* @shellData: Pointer to the custom shell data structure.
* Return: 1 if the parameters are NULL, 2 an error, or 0 if successful.
*/
int setenvironmentVariable(char *key, char *value, CustomShellData *shellData)
{
int i, keyL = 0, isNewKey = 1;

/* Validate the arguments */
if (key == NULL || value == NULL || shellData->env == NULL)
return (1);

/* Determine the length of the variable name */
keyL = strLength(key);

for (i = 0; shellData->env[i]; i++)
{
/* Iterate through the environment and check for a match */
if (strCompare(key, shellData->env[i], keyL) &&
shellData->env[i][keyL] == '=')
{
/* If the key already exists, free the entire variable */
isNewKey = 0;
free(shellData->env[i]);
break;
}
}

/* Create a string in the format "key=value" */
shellData->env[i] = strConcat(strDuplicate(key), "=");
shellData->env[i] = strConcat(shellData->env[i], value);

if (isNewKey)
{
/* created at the end of we need to put a NULL in the next position */
shellData->env[i + 1] = NULL;
}

return (0);
}

/**
* removeEnvironmentVariable - Remove a key from the environment.
* @key: The key to remove.
* @shellData:  Pointer to the custom shell data structure.
* Return: 1 if the key was removed, 0 if the key does not exist.
*/
int removeEnvironmentVariable(char *key, CustomShellData *shellData)
{
int i, keyL = 0;

/* Validate the arguments */
if (key == NULL || shellData->env == NULL)
return (0);

/* Determine the length of the variable name */
keyL = strLength(key);

for (i = 0; shellData->env[i]; i++)
{
/* Iterate through the environment and check for a match */
if (strCompare(key, shellData->env[i], keyL) &&
shellData->env[i][keyL] == '=')
{
/* If the key already exists, remove it */
free(shellData->env[i]);

/* Move the other keys one position down */
i++;
for (; shellData->env[i]; i++)
{
shellData->env[i - 1] = shellData->env[i];
}

/* Put a NULL value at the new end of the list */
shellData->env[i - 1] = NULL;
return (1);
}
}
return (0);
}

/**
* printEnvironment - Print the current environment.
* @shellData: Struct for the program's data.
* Return: Nothing.
*/
void printEnvironment(CustomShellData *shellData)
{
int jx;

for (jx = 0; shellData->env[jx]; jx++)
{
printToStdout(shellData->env[jx]);
printToStdout("\n");
}
}

