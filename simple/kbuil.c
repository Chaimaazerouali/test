#include "my_shell.h"

/**
 * exitShell - Exit the program with a specified status code.
 * @program_data: A structure containing program data.
 * Return: 0 if successful, or another number if specified in the arguments.
 */
int exitShell(CustomShellData *program_data)
{
    int idx;

    if (program_data->tokens[1] != NULL)
    {
        /* If there is an argument for exit, check if it's a number */
        for (idx = 0; program_data->tokens[1][idx]; idx++)
        {
            if ((program_data->tokens[1][idx] < '0' || program_data->tokens[1][idx] > '9') && program_data->tokens[1][idx] != '+')
            {
                errno = EINVAL;
                return EINVAL;
            }
        }
        errno = parseInt(program_data->tokens[1]);
    }
    free_all_shell_data(program_data);
    exit(errno);
}

/**
 * changeDirectory - Change the current directory.
 * @program_data: A structure containing program data.
 * Return: 0 if successful, or another number if specified in the arguments.
 */
int changeDirectory(CustomShellData *program_data)
{
    char *home_directory = getEnvironmentVariable("HOME", program_data);
    char *old_directory = NULL;
    char previous_directory[128] = {0};
    int error_code = 0;

    if (program_data->tokens[1])
    {
        if (strCompare(program_data->arguments[1], "-", 0))
        {
            old_directory = getEnvironmentVariable("OLDPWD", program_data);
            if (old_directory)
                error_code = setWorkingDirectory(program_data, old_directory);
            printToStdout(getEnvironmentVariable("PWD", program_data));
            printToStdout("\n");

            return error_code;
        }
        else
        {
            return setWorkingDirectory(program_data, program_data->arguments[1]);
        }
    }
    else
    {
        if (!home_directory)
            home_directory = getcwd(previous_directory, 128);

        return setWorkingDirectory(program_data, home_directory);
    }

    return 0;
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
            errno = ENOENT;
            return ENOENT;
        }
        setEnvironmentVariable("PWD", new_directory, program_data);
    }
    setEnvironmentVariable("OLDPWD", previous_directory, program_data);
    return 0;
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

    messages[0] = HELP_MESSAGE;

    /* Validate arguments */
    if (program_data->tokens[1] == NULL)
    {
        printToStdout(messages[0] + 6);
        return 1;
    }
    if (program_data->tokens[2] != NULL)
    {
        errno = E2BIG;
        perror(program_data->program_name);
        return 5;
    }
    messages[1] = HELP_EXIT_MESSAGE;
    messages[2] = HELP_ENV_MESSAGE;
    messages[3] = HELP_SETENV_MESSAGE;
    messages[4] = HELP_UNSETENV_MESSAGE;
    messages[5] = HELP_CD_MESSAGE;

    for (idx = 0; messages[idx]; idx++)
    {
        length = strLengh(program_data->tokens[1]);
        if (strCompare(program_data->tokens[1], messages[idx], length))
        {
            printToStdout(messages[idx] + length + 1);
            return 1;
        }
    }
    /* If there is no match, print an error and return -1 */
    errno = EINVAL;
    perror(program_data->program_name);
    return 0;
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
    if (program_data->arguments[1] == NULL)
        return showAliases(program_data, NULL);

    while (program_data->tokens[++idx])
    {
        /* If there are arguments, set or print each alias */
        if (countCharacterOccurrences(program_data->arguments[idx], "="))
            setAlias(program_data->tokens[idx], program_data);
        else
            showAliases(program_data, program_data->tokens[idx])

    return 0;
}

