#include "sheel.h"


/**
 * free_recurring_data- Frees the fields needed at each loop iteration.
 * @data: A pointer to the program's data.
 * Return: Nothing.
 */
void free_recurring_data(CustomShellData *data)
{
    if (data->tokens)
        free_pointer_array(data->tokens);
    if (data->input_line)
        free(data->input_line);
    if (data->command_name)
        free(data->command_name);

    data->input_line = NULL;
    data->command_name = NULL;
    data->tokens = NULL;
}

/**
 * free_all_shell_data - Frees all fields of the program's data.
 * @data: A pointer to the program's data.
 * Return: Nothing.
 */
void free_all_shell_data(CustomShellData *data)
{
    if (data->file_descriptor != 0)
    {
        if (close(data->file_descriptor))
            perror(data->program_name);
    }
    free_recurring_data(data);
    free_pointer_array(data->env);
    free_pointer_array(data->alias_list);
}

/**
 * free_pointer_array - Frees each pointer in an array of pointers and the array itself.
 * @array: The array of pointers.
 * Return: Nothing.
 */
void free_pointer_array(char **array)
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

