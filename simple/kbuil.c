#include "sheel.h"

/**
* exitShell - Exit the program with a specified status code.
* @d: A structure containing program data.
* Return: 0 if successful, or another number if specified in the arguments.
*/
int exitShell(CustomShellData *d)
{
int x;

if (d->tokens[1] != NULL)
{
/* If there is an argument for exit, check if it's a number */
for (x = 0; d->tokens[1][x]; x++)
{
if ((d->tokens[1][x] < '0' || d->tokens[1][x] > '9') && d->tokens[1][x] != '+')
{
errno = 2;
return (2);
}
}
errno = parseInt(d->tokens[1]);
}
free_all_shell_data(d);
exit(errno);
}

/**
* changeDirectory - Change the current directory.
* @program_data: A structure containing program data.
* Return: 0 if successful, or another number if specified in the arguments.
*/
int changeDirectory(CustomShellData *program_data)
{
char *homeDirectory = getEnvironmentVariable("HOME", program_data);
char *previousDirectory = NULL;
char previous_dir[128] = {0};
int error_code = 0;

if (program_data->tokens[1])
{
if (strCompare(program_data->tokens[1], "-", 0))
{
previousDirectory = getEnvironmentVariable("OLDPWD", program_data);
if (previousDirectory)
error_code = setWorkingDirectory(program_data, previousDirectory);
printToStdout(getEnvironmentVariable("PWD", program_data));
printToStdout("\n");

return (error_code);
}
else
{
return (setWorkingDirectory(program_data, program_data->tokens[1]));
}
}
else
{
if (!homeDirectory)
homeDirectory = getcwd(previous_dir, 128);

return (setWorkingDirectory(program_data, homeDirectory));
}
return (0);
}
/**
* setWorkingDirectory - Set the working directory.
* @program_data: A structure containing program data.
* @new_directory: The path to be set as the working directory.
* Return: 0 if successful, or another number if specified in the arguments.
*/
int setWorkingDirectory(CustomShellData *program_data, char *new_directory)
{
char previous_directory[128] = {0};
int error_code = 0;

getcwd(previous_directory, 128);

if (!strCompare(previous_directory, new_directory, 0))
{
error_code = chdir(new_directory);
if (error_code == -1)
{
errno = 2;
return (3);
}
setenvironmentVariable("PWD", new_directory, program_data);
}
setenvironmentVariable("OLDPWD", previous_directory, program_data);
return (0);
}

/**
* displayHelp - Display information about the shell environment.
* @program_data: A structure containing program data.
* Return: 0 if successful, or another number if specified in the arguments.
*/
int displayHelp(CustomShellData *program_data)
{
int idx, length = 0;
char *messages[6] = {NULL};

messages[0] = CUSTOM_HELP_MSG;

/* Validate arguments */
if (program_data->tokens[1] == NULL)
{
printToStdout(messages[0] + 6);
return (1);
}
if (program_data->tokens[2] != NULL)
{
errno = E2BIG;
perror(program_data->program_name);
return (5);
}
messages[1] = CUSTOM_HELP_EXIT_MSG;
messages[2] = CUSTOM_HELP_ENV_MSG;
messages[3] = CUSTOM_HELP_SETENV_MSG;
messages[4] = CUSTOM_HELP_UNSETENV_MSG;
messages[5] = CUSTOM_HELP_CD_MSG;

for (idx = 0; messages[idx]; idx++)
{
length = strLength(program_data->tokens[1]);
if (strCompare(program_data->tokens[1], messages[idx], length))
{
printToStdout(messages[idx] + length + 1);
return (1);
}
}
/* If there is no match, print an error and return -1 */
errno = EINVAL;
perror(program_data->program_name);
return (0);
}

/**
* manageAliases - Add, remove, or show aliases.
* @program_data: A structure containing program data.
* Return: 0 if successful, or another number if specified in the arguments.
*/
int manageAliases(CustomShellData *program_data)
{
int idx = 0;

/* If there are no arguments, print all aliases */
if (program_data->tokens[1] == NULL)
return (showAliases(program_data, NULL));

while (program_data->tokens[++idx])
{
/* If there are arguments, set or print each alias */
if (countCharacterOccurrences(program_data->tokens[idx], "="))
setAlias(program_data->tokens[idx], program_data);
else
showAliases(program_data, program_data->tokens[idx]);
}
return (0);
}

