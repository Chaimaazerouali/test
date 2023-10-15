#include "sheel.h"

/**
 * getEnvironmentVariable - Get the value of an environment variable.
 * @key: The name of the environment variable of interest.
 * @data: Struct for the program's data.
 * Return: A pointer to the value of the variable, or NULL if it doesn't exist.
 */
char *getEnvironmentVariable(char *key, CustomShellData *data)
{
    int i, keyLength = 0;

    /* Validate the arguments */
    if (key == NULL || data->env == NULL)
        return (NULL);

    /* Obtain the length of the variable requested */
    keyLength = strLength(key);

    for (i = 0; data->env[i]; i++)
    {
        /* Iterate through the environment and check for a match */
        if (strCompare(key, data->env[i], keyLength) &&
            data->env[i][keyLength] == '=')
        {
            /* Return the value of the key in the format "NAME=value" */
            return (data->env[i] + keyLength + 1);
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
 * @data: Struct for the program's data.
 * Return: 1 if the parameters are NULL, 2 if there is an error, or 0 if successful.
 */
int setenvironmentVariable(char *key, char *value, CustomShellData *data)
{
    int i, keyLength = 0, isNewKey = 1;

    /* Validate the arguments */
    if (key == NULL || value == NULL || data->env == NULL)
        return (1);

    /* Obtain the length of the variable requested */
    keyLength = strLength(key);

    for (i = 0; data->env[i]; i++)
    {
        /* Iterate through the environment and check for a match */
        if (strCompare(key, data->env[i], keyLength) &&
            data->env[i][keyLength] == '=')
        {
            /* If the key already exists, free the entire variable */
            isNewKey = 0;
            free(data->env[i]);
            break;
        }
    }

    /* Create a string in the format "key=value" */
    data->env[i] = strConcat(strDuplicate(key), "=");
    data->env[i] = strConcat(data->env[i], value);

    if (isNewKey)
    {
        /* If the variable is new, it is created at the end of the current list
           and we need to put a NULL value in the next position */
        data->env[i + 1] = NULL;
    }

    return (0);
}

/**
 * removeEnvironmentVariable - Remove a key from the environment.
 * @key: The key to remove.
 * @data: Struct for the program's data.
 * Return: 1 if the key was removed, 0 if the key does not exist.
 */
int removeEnvironmentVariable(char *key, CustomShellData *data)
{
    int i, keyLength = 0;

    /* Validate the arguments */
    if (key == NULL || data->env == NULL)
        return (0);

    /* Obtain the length of the variable requested */
    keyLength = strLength(key);

    for (i = 0; data->env[i]; i++)
    {
        /* Iterate through the environment and check for a match */
        if (strCompare(key, data->env[i], keyLength) &&
            data->env[i][keyLength] == '=')
        {
            /* If the key already exists, remove it */
            free(data->env[i]);

            /* Move the other keys one position down */
            i++;
            for (; data->env[i]; i++)
            {
                data->env[i - 1] = data->env[i];
            }

            /* Put a NULL value at the new end of the list */
            data->env[i - 1] = NULL;
            return (1);
        }
    }
    return (0);
}

/**
 * printEnvironment - Print the current environment.
 * @data: Struct for the program's data.
 * Return: Nothing.
 */
void printEnvironment(CustomShellData *data)
{
    int j;

    for (j = 0; data->env[j]; j++)
    {
        printToStdout(data->env[j]);
        printToStdout("\n");
    }
}

