#include "shell.h"

/**
 * freeRecurrentData - Frees the fields needed at each loop iteration.
 * @data: A pointer to the program's data.
 * Return: Nothing.
 */
void freeRecurrentData(CustomShellData *data)
{
    if (data->tokens)
        freeArrayOfPointers(data->tokens);
    if (data->input_line)
        free(data->input_line);
    if (data->command_name)
        free(data->command_name);

    data->input_line = NULL;
    data->command_name = NULL;
    data->tokens = NULL;
}

/**
 * freeAllData - Frees all fields of the program's data.
 * @data: A pointer to the program's data.
 * Return: Nothing.
 */
void freeAllData(CustomShellData *data)
{
    if (data->file_descriptor != 0)
    {
        if (close(data->file_descriptor))
            perror(data->program_name);
    }
    freeRecurrentData(data);
    freeArrayOfPointers(data->env);
    freeArrayOfPointers(data->alias_list);
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

