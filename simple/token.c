#include "shell.h"

/**
 * customTokenizer - This function separates the string using a designated delimiter.
 * @data: A pointer to the program's data.
 * Return: An array of the different parts of the string.
 */
void customTokenizer(data_of_program *data)
{
    char *customDelimiter = " \t";
    int i, j, tokenCounter = 2, strLength;

    strLength = customStrLength(data->input_line);
    if (strLength)
    {
        if (data->input_line[strLength - 1] == '\n')
            data->input_line[strLength - 1] = '\0';
    }

    for (i = 0; data->input_line[i]; i++)
    {
        for (j = 0; customDelimiter[j]; j++)
        {
            if (data->input_line[i] == customDelimiter[j])
                tokenCounter++;
        }
    }

    data->tokens = malloc(tokenCounter * sizeof(char *));
    if (data->tokens == NULL)
    {
        perror(data->program_name);
        exit(errno);
    }
    i = 0;
    data->tokens[i] = customStrDuplicate(customStrtok(data->input_line, customDelimiter));
    data->command_name = customStrDuplicate(data->tokens[0]);
    while (data->tokens[i++])
    {
        data->tokens[i] = customStrDuplicate(customStrtok(NULL, customDelimiter));
    }
}

