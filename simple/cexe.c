#include "sheel.h"

/**
 * executeCommand - Execute a command with its full path and environment variables.
 * @data: A pointer to the program's data structure.
 * Return: 0 if successful, -1 on failure.
 */
int executeCommand(CustomShellData *data)
{
    int returnStatus = 0, childStatus;
    pid_t childPid;

    /* Check if the program is a built-in command */
    returnStatus = executeBuiltIn(data);
    if (returnStatus != -1)
    {
        /* If the program was found among built-ins, execute it */
        return (returnStatus);
    }

    /* Check for the program in the file system */
    returnStatus = findProgramInPath(data);
    if (returnStatus)
    {
        /* If the program was not found, return an error */
        return (returnStatus);
    }
    else
    {
        /* If the program was found, create a child process */
        childPid = fork();

        if (childPid == -1)
        {
            /* If the fork call failed, print an error and exit */
            perror(data->command_name);
            exit(EXIT_FAILURE);
        }

        if (childPid == 0)
        {
            /* Child process: execute the program */
            returnStatus = execve(data->tokens[0], data->tokens, data->env);

            if (returnStatus == -1)
            {
                /* If there was an error with execve, print an error and exit */
                perror(data->command_name);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process: wait for the child process and check its exit status */
            wait(&childStatus);

            if (WIFEXITED(childStatus))
                errno = WEXITSTATUS(childStatus);
            else if (WIFSIGNALED(childStatus))
                errno = 128 + WTERMSIG(childStatus);
        }
    }
    return (0);
}

