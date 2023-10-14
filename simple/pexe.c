#include "sheel.h"

/**
 * expandVariables - Expand variables
 * @data: A pointer to a struct containing program data.
 *
 * This function expands variables in the input line based on certain patterns.
 * For example, it replaces "$?" with the value of the "errno" variable.
 *
 * Return: Nothing, but sets errno on error.
 */
void expandVariables(CustomShellData *data)
{
    int index1, index2;
    char inputCopy[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

    if (data->input_line == NULL)
        return;

    bufferAdd(inputCopy, data->input_line);

    for (index1 = 0; inputCopy[index1]; index1++)
    {
        if (inputCopy[index1] == '#')
        {
            inputCopy[index1--] = '\0';
        }
        else if (inputCopy[index1] == '$' && inputCopy[index1 + 1] == '?')
        {
            inputCopy[index1] = '\0';
            convertLongToString(errno, expansion, 10);
            bufferAdd(inputCopy, expansion);
            bufferAdd(inputCopy, data->inputLine + index1 + 2);
        }
        else if (inputCopy[index1] == '$' && inputCopy[index1 + 1] == '$')
        {
            inputCopy[index1] = '\0';
            convertLongToString(getpid(), expansion, 10);
            bufferAdd(inputCopy, expansion);
            bufferAdd(inputCopy, data->input_line + index1 + 2);
        }
        else if (inputCopy[index1] == '$' && (inputCopy[index1 + 1] == ' ' || inputCopy[index1 + 1] == '\0'))
        {
            continue;
        }
        else if (inputCopy[index1] == '$')
        {
            for (index2 = 1; inputCopy[index1 + index2] && inputCopy[index1 + index2] != ' '; index2++)
            {
                expansion[index2 - 1] = inputCopy[index1 + index2];
            }
            temp = getEnvVariable(expansion, data);
            inputCopy[index1] = '\0';
            expansion[0] = '\0';
            bufferAdd(expansion, inputCopy + index1 + index2);
            temp ? bufferAdd(inputCopy, temp) : 1;
            bufferAdd(inputCopy, expansion);
        }
    }

    if (!strCompare(data->inputLine, inputCopy, 0))
    {
        free(data->input_line);
        data->input_line = strDuplicate(inputCopy);
    }
}

/**
 * expandAliases - Expand aliases
 * @data: A pointer to a struct containing program data.
 *
 * This function expands aliases in the input line. If an alias is found in
 * the input, it is replaced with its corresponding value.
 *
 * Return: Nothing, but sets errno on error.
 */
void expandAliases(CustomShellData *data)
{
    int index1, index2, wasExpanded = 0;
    char inputCopy[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

    if (data->input_line == NULL)
        return;

    bufferAdd(inputCopy, data->input_line);

    for (index1 = 0; inputCopy[index1]; index1++)
    {
        for (index2 = 0; inputCopy[index1 + index2] && inputCopy[index1 + index2] != ' '; index2++)
        {
            expansion[index2] = inputCopy[index1 + index2];
        }
        expansion[index2] = '\0';
        temp = getAliasValue(data, expansion);

        if (temp)
        {
            expansion[0] = '\0';
            bufferAdd(expansion, inputCopy + index1 + index2);
            inputCopy[index1] = '\0';
            bufferAdd(inputCopy, temp);
            inputCopy[strlen(inputCopy)] = '\0';
            bufferAdd(inputCopy, expansion);
            wasExpanded = 1;
        }
        break;
    }

    if (wasExpanded)
    {
        free(data->input_line);
        data->input_line = strDuplicate(inputCopy);
    }
}

/**
 * bufferAdd - Append a string to another string
 * @dest: The destination string.
 * @src: The source string to be appended.
 *
 * Return: Nothing.
 */
int bufferAdd(char *dest, char *src)
{
    int destLength, srcLength, i;

    destLength = strLength(dest);
    srcLength = strLength(src);

    for (i = 0; src[i]; i++)
    {
        dest[destLength + i] = src[i];
    }

    dest[destLength + i] = '\0';
}

