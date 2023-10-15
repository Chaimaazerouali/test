#include "sheel.h"

/**
 * showEnvironment - Display the current environment variables.
 * @data: A struct containing program data.
 * Return: 0 on success, or an error code if specified in the arguments.
 */
int showEnvironment(CustomShellData *data)
{
    int index;
    char var_name[50] = {'\0'};
    char *var_copy = NULL;

    /* If no arguments, display the environment variables */
    if (data->tokens[1] == NULL)
        printEnvironment(data);
    else
    {
        for (index = 0; data->tokens[1][index]; index++)
        {
            /* Check if there's a '=' character in the argument */
            if (data->tokens[1][index] == '=')
            {
                /* Check if there's a variable with the same name and temporarily change its value */
                var_copy = strDuplicate(getEnvironmentVariable(var_name, data));

                if (var_copy != NULL)
                    setenvironmentVariable(var_name, data->tokens[1] + index + 1, data);

                /* Print the environment */
                printEnvironment(data);

                if (getEnvironmentVariable(var_name, data) == NULL)
                {
                    /* Print the variable if it does not exist in the environment */
                    printToStdout(data->tokens[1]);
                    printToStdout("\n");
                }
                else
                {
                    /* Return the old value of the variable */
                    setenvironmentVariable(var_name, var_copy, data);
                    free(var_copy);
                }
                return 0;
            }
            var_name[index] = data->tokens[1][index];
        }

        errno = 2;
        perror(data->command_name);
        errno = 127;
    }
    return 0;
}

/**
 * setEnvironmentVariable - Set or update an environment variable.
 * @data: A struct containing program data.
 * Return: 0 on success, or an error code if specified in the arguments.
 */
int setEnvironmentVariable(CustomShellData *data)
{
    if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	setenvironmentVariable(data->tokens[1], data->tokens[2], data);

	return (0);
}
/**
 * unsetEnvironmentVariable - Remove an environment variable.
 * @data: A struct containing program data.
 * Return: 0 on success, or an error code if specified in the arguments.
 */
int unsetEnvironmentVariable(CustomShellData *data)
{
    /* Validate arguments */
    if (data->tokens[1] == NULL)
        return 0;

    if (data->tokens[2] != NULL)
    {
        errno = E2BIG;
        perror(data->command_name);
        return 5;
    }

    removeEnvironmentVariable(data->tokens[1], data);
    return 0;
}

