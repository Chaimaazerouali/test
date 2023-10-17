#include "sheel.h"

/**
* printToStdout - Writes an array of characters to standard output.
* @str: Pointer to the array of characters.
* Return: The number of bytes written.
* On error, -1 is returned, and errno is set appropriately.
*/
int printToStdout(char *str)
{
return (write(STDOUT_FILENO, str, strLength(str)));
}

/**
* printToStderr - Writes an array of characters to standard error.
* @str: Pointer to the array of characters.
* Return: The number of bytes written.
* On error, -1 is returned, and errno is set appropriately.
*/
int printToStderr(char *str)
{
return (write(STDERR_FILENO, str, strLength(str)));
}

/**
* printErrorMessage - Writes an error message to standard error.
* @errorCode: The error code to print.
* @data: A pointer to the program's data.
* Return: The number of bytes written.
* On error, -1 is returned, and errno is set appropriately.
*/
int printErrorMessage(int errorCode, CustomShellData *data)
{
char counterAsString[10] = {'\0'};

convertLongToString((long)data->exec_counter, counterAsString, 10);

if (errorCode == 2 || errorCode == 3)
{
printToStderr(data->program_name);
printToStderr(": ");
printToStderr(counterAsString);
printToStderr(": ");
printToStderr(data->tokens[0]);
if (errorCode == 2)
printToStderr(": Illegal number: ");
else
printToStderr(": can't cd to ");
printToStderr(data->tokens[1]);
printToStderr("\n");
}
else if (errorCode == 127)
{
printToStderr(data->program_name);
printToStderr(": ");
printToStderr(counterAsString);
printToStderr(": ");
printToStderr(data->command_name);
printToStderr(": not found\n");
}
else if (errorCode == 126)
{
printToStderr(data->program_name);
printToStderr(": ");
printToStderr(counterAsString);
printToStderr(": ");
printToStderr(data->command_name);
printToStderr(": Permission denied\n");
}
return (0);
}

