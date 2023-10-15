#include "sheel.h"

int isFileExecutable(char *fullPath);

/**
 * findProgramInPath - Searches for a program in the directories listed in PATH.
 * @data: A pointer to the program's data.
 * Return: 0 if the program is found and executable, error code otherwise.
 */
int findProgramInPath(CustomShellData*data)
{
    int i = 0, returnCode = 0;
    char **directories;

    if (!data->command_name)
        return (2);

    if (data->command_name[0] == '/' || data->command_name[0] == '.')
        return isFileExecutable(data->command_name);

    free(data->tokens[0]);
    data->tokens[0] = strConcat(strDuplicate("/"), data->command_name);
    if (!data->tokens[0])
        return (2);

    directories = tokenizePath(data);

    if (!directories || !directories[0])
    {
        errno = 127;
        return (127);
    }

    for (i = 0; directories[i]; i++)
    {
        directories[i] = strConcat(directories[i], data->tokens[0]);
        returnCode = isFileExecutable(directories[i]);

        if (returnCode == 0 || returnCode == 126)
        {
            errno = 0;
            free(data->tokens[0]);
            data->tokens[0] = strDuplicate(directories[i]);
            free_pointer_array(directories);
            return (returnCode);
        }
    }

    free(data->tokens[0]);
    data->tokens[0] = NULL;
    free_pointer_array(directories);
    return (returnCode);
}

/**
 * tokenizePath - Tokenizes the PATH into directories.
 * @data: A pointer to the program's data.
 * Return: Array of path directories.
 */
char **tokenizePath(CustomShellData *data)
{
    int i = 0;
    int numDirectories = 2;
    char **tokens = NULL;
    char *pathValue;

    pathValue = getEnvironmentVariable("PATH", data);

    if ((pathValue == NULL) || pathValue[0] == '\0')
    {
        return (NULL);
    }

    pathValue = strDuplicate(pathValue);

    for (i = 0; pathValue[i]; i++)
    {
        if (pathValue[i] == ':')
        {
            numDirectories++;
        }
    }

    tokens = malloc(sizeof(char *) * numDirectories);
    i = 0;
    tokens[i] = strDuplicate(customStrtok(pathValue, ":"));

    while (tokens[i++])
    {
        tokens[i] = strDuplicate(customStrtok(NULL, ":"));
    }

    free(pathValue);
    pathValue = NULL;
    return (tokens);
}

/**
 * isFileExecutable - Checks if a file exists, is not a directory,
 * and has execution permissions.
 * @fullPath: Pointer to the full file name.
 * Return: 0 on success, or error code if it exists.
 */
int isFileExecutable(char *fullPath)
{
    struct stat fileStat;

    if (stat(fullPath, &fileStat) != -1)
    {
        if (S_ISDIR(fileStat.st_mode) || access(fullPath, X_OK))
        {
            errno = 126;
            return (126);
        }
        return (0);
    }

    errno = 127;
    return (127);
}

