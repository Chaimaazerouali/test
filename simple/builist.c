#include "shell.h"

/**
 * executeBuiltin - Executes the appropriate builtin command.
 * @data: Struct containing program data.
 * Return: Returns the return value of the executed function if there is a match,
 * otherwise returns -1.
 **/
int executeBuiltin(data_of_program *data)
{
    int iterator;
    builtins builtinCommands[] = {
        {"exit", builtinExit},
        {"help", builtinHelp},
        {"cd", builtinCd},
        {"alias", builtinAlias},
        {"env", builtinShowEnvironment},
        {"setenv", builtinSetEnvironment},
        {"unsetenv", builtinUnsetEnvironment},
        {NULL, NULL}
    };

    /* Iterate through the builtinCommands array */
    for (iterator = 0; builtinCommands[iterator].builtin != NULL; iterator++)
    {
        /* Check for a match between the given command and a builtin */
        if (str_compare(builtinCommands[iterator].builtin, data->command_name, 0))
        {
            /* Execute the function and return its return value */
            return (builtinCommands[iterator].function(data));
        }
    }

    /* If there is no match, return -1 */
    return (-1);
}

