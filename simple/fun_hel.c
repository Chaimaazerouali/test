#include "shell.h"

/**
 * freeRecurrentData - Frees the fields needed at each loop iteration.
 * @data: A pointer to the program's data.
 * Return: Nothing.
 */
void freeRecurrentData(data_of_program *data)
{
    if (data->tokens)
        freeArrayOfPointers(data->tokens);
    if (data->inputLine)
        free(data->inputLine);
    if (data->commandName)
        free(data->commandName);

    data->inputLine = NULL;
    data->commandName = NULL;
    data->tokens = NULL;
}

/**
 * freeAllData - Frees all fields of the program's data.
 * @data: A pointer to the program's data.
 * Return: Nothing.
 */
void freeAllData(data_of_program *data)
{
    if (data->fileDescriptor != 0)
    {
        if (close(data->fileDescriptor))
            perror(data->programName);
    }
    freeRecurrentData(data);
    freeArrayOfPointers(data->environment);
    freeArrayOfPointers(data->aliasList);
}

/**
 * freeArrayOfPointers - Frees each pointer in an array of pointers and the array itself.
 * @array: The array of pointers.
 * Return: Nothing.
 */
void freeArrayOfPointers(char **array)
{
    int i;

    if (array != NULL)
    {
        for (i = 0; array[i]; i++)
            free(array[i]);

        free(array);
        array = NULL;
    }
}

