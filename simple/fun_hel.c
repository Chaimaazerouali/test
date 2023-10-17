#include "sheel.h"

/**
* free_recurring_data - Frees the fields needed at each loop iteration.
* @shelldata: A pointer to the program's data.
* Return: Nothing.
*/
void free_recurring_data(CustomShellData *shelldata)
{
if (shelldata->tokens)
free_pointer_array(shelldata->tokens);
if (shelldata->input_line)
free(shelldata->input_line);
if (shelldata->command_name)
free(shelldata->command_name);

shelldata->input_line = NULL;
shelldata->command_name = NULL;
shelldata->tokens = NULL;
}

/**
* free_all_shell_data - Frees all fields of the program's data.
* @shelldata: A pointer to the program's data.
* Return: Nothing.
*/
void free_all_shell_data(CustomShellData *shelldata)
{
if (shelldata->file_descriptor != 0)
{
if (close(shelldata->file_descriptor))
perror(shelldata->program_name);
}
free_recurring_data(shelldata);
free_pointer_array(shelldata->env);
free_pointer_array(shelldata->alias_list);
}

/**
* free_pointer_array - pointer in an array of pointers and the array itself.
* @ary: The array of pointers.
* Return: Nothing.
*/
void free_pointer_array(char **ary)
{
int i;

if (ary != NULL)
{
for (i = 0; ary[i]; i++)
free(ary[i]);

free(ary);
ary = NULL;
}
}

