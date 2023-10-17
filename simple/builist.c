#include "sheel.h"

/**
* executeBuiltin - Executes the appropriate builtin command.
* @data: Struct containing program data.
* Return: Returns the return value of the executed funct if there is a match,
* otherwise returns -1.
**/
int executeBuiltin(CustomShellData *data)
{
int iter;
ShellBuiltins builtinCommands[] = {
{"exit", exitShell},
{"help", displayHelp},
{"cd", changeDirectory},
{"alias", manageAliases},
{"env", showEnvironment},
{"setenv", setEnvironmentVariable},
{"unsetenv", unsetEnvironmentVariable},
{NULL, NULL}
};

/* Iterate through the builtinCommands array */
for (iter = 0; builtinCommands[iter].builtin != NULL; iter++)
{
/* Check for a match between the given command and a builtin */
if (strCompare(builtinCommands[iter].builtin, data->command_name, 0))
{
/* Execute the function and return its return value */
return (builtinCommands[iter].function(data));
}
}

/* If there is no match, return -1 */
return (-1);
}

