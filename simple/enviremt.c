#include "shell.h"

/**
 * showEnvironment - Displays the current environment.
 * @data: Struct for the program's data.
 * Return: 0 if success, 1 if there are arguments.
 */
int showEnvironment(CustomShellData *data)
{
    int i;

    if (data->tokens[1] != NULL)
    {
        errno = E2BIG;
        perror(data->command_name);
        return 1;
    }

    printEnvironment(data);

    return 0;
}

/**
 * setEnvironmentVariable - Sets or updates an environment variable.
 * @data: Struct for the program's data.
 * Return: 0 if success, 1 if there are missing arguments, 2 if arguments are too big.
 */
int setEnvironmentVariable(CustomShellData *data)
{
    if (data->tokens[1] == NULL || data->tokens[2] == NULL || data->tokens[3] != NULL)
    {
        errno = E2BIG;
        perror(data->command_name);
        return 1;
    }

    int result = setEnvironmentVariable(data->tokens[1], data->tokens[2], data);

    if (result == 0)
        return 0;
    else
        return 2;
}

/**
 * unsetEnvironmentVariable - Unsets an environment variable.
 * @data: Struct for the program's data.
 * Return: 0 if success, 1 if there are missing arguments.
 */
int unsetEnvironmentVariable(CustomShellData *data)
{
    if (data->tokens[1] == NULL || data->tokens[2] != NULL)
    {
        errno = E2BIG;
        perror(data->command_name);
        return 1;
    }

    removeEnvironmentVariable(data->tokens[1], data);

    return 0;
}

