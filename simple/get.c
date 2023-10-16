#include "sheel.h"

int custom_getline(CustomShellData *data)
{
    char buff[BUFFER_SIZE] = {'\0'};
    static char *array_commands[10] = {NULL};
    static char array_operators[10] = {'\0'};
    ssize_t bytes_read;
    int i = 0;

    if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
        (array_operators[0] == '|' && errno == 0))
    {
        for (i = 0; array_commands[i]; i++)
        {
            free(array_commands[i]);
            array_commands[i] = NULL;
        }

        bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
        if (bytes_read == 0)
            return (-1);

        i = 0;
        do {
            array_commands[i] = strDuplicate(customStrtok(i ? NULL : buff, "\n;"));
            i = check_logical_operators(array_commands, i, array_operators);
        } while (array_commands[i++]);
    }

    data->input_line = array_commands[0];
    for (i = 0; array_commands[i]; i++)
    {
        array_commands[i] = array_commands[i + 1];
        array_operators[i] = array_operators[i + 1];
    }

    return (strLength(data->input_line));
}

int check_logical_operators(char *array_commands[], int i, char array_operators[])
{
    char *temp = NULL;
    int jx;

    for (jx = 0; array_commands[i] != NULL  && array_commands[i][jx]; jx++)
    {
        if (array_commands[i][jx] == '&' && array_commands[i][jx + 1] == '&')
        {
            temp = array_commands[i];
            array_commands[i][jx] = '\0';
            array_commands[i] = strDuplicate(array_commands[i]);
            array_commands[i + 1] = strDuplicate(temp + jx + 2);
            i++;
            array_operators[i] = '&';
            free(temp);
            jx = 0;
        }
        if (array_commands[i][jx] == '|' && array_commands[i][jx + 1] == '|')
        {
            temp = array_commands[i];
            array_commands[i][jx] = '\0';
            array_commands[i] = strDuplicate(array_commands[i]);
            array_commands[i + 1] = strDuplicate(temp + jx + 2);
            i++;
            array_operators[i] = '|';
            free(temp);
            jx=0;
        }
    }
    return (i);
}

