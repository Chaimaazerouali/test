#include "shell.h"

/**
 * expandVariables - Expand variables
 * @data: A pointer to a struct containing program data.
 *
 * This function expands variables in the input line based on certain patterns.
 * For example, it replaces "$?" with the value of the "errno" variable.
 *
 * Return: Nothing, but sets errno on error.
 */
void expandVariables(data_of_program *data)
{
    int index1, index2;
    char inputCopy[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

    if (data->inputLine == NULL)
        return;

    copyString(inputCopy, data->inputLine);

    for (index1 = 0; inputCopy[index1]; index1++)
    {
        if (inputCopy[index1] == '#')
        {
            inputCopy[index1--] = '\0';
        }
        else if (inputCopy[index1] == '$' && inputCopy[index1 + 1] == '?')
        {
            inputCopy[index1] = '\0';
            longToString(errno, expansion, 10);
            appendString(inputCopy, expansion);
            appendString(inputCopy, data->inputLine + index1 + 2);
        }
        else if (inputCopy[index1] == '$' && inputCopy[index1 + 1] == '$')
        {
            inputCopy[index1] = '\0';
            longToString(getpid(), expansion, 10);
            appendString(inputCopy, expansion);
            appendString(inputCopy, data->inputLine + index1 + 2);
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
            appendString(expansion, inputCopy + index1 + index2);
            temp ? appendString(inputCopy, temp) : 1;
            appendString(inputCopy, expansion);
        }
    }

    if (!compareStrings(data->inputLine, inputCopy, 0))
    {
        free(data->inputLine);
        data->inputLine = duplicateString(inputCopy);
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
void expandAliases(data_of_program *data)
{
    int index1, index2, wasExpanded = 0;
    char inputCopy[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

    if (data->inputLine == NULL)
        return;

    copyString(inputCopy, data->inputLine);

    for (index1 = 0; inputCopy[index1]; index1++)
    {
        for (index2 = 0; inputCopy[index1 + index2] && inputCopy[index1 + index2] != ' '; index2++)
        {
            expansion[index2] = inputCopy[index1 + index2];
        }
        expansion[index2] = '\0';
        temp = getAlias(data, expansion);

        if (temp)
        {
            expansion[0] = '\0';
            appendString(expansion, inputCopy + index1 + index2);
            inputCopy[index1] = '\0';
            appendString(inputCopy, temp);
            inputCopy[strlen(inputCopy)] = '\0';
            appendString(inputCopy, expansion);
            wasExpanded = 1;
        }
        break;
    }

    if (wasExpanded)
    {
        free(data->inputLine);
        data->inputLine = duplicateString(inputCopy);
    }
}

/**
 * appendString - Append a string to another string
 * @dest: The destination string.
 * @src: The source string to be appended.
 *
 * Return: Nothing.
 */
void appendString(char *dest, char *src)
{
    int destLength, srcLength, i;

    destLength = stringLength(dest);
    srcLength = stringLength(src);

    for (i = 0; src[i]; i++)
    {
        dest[destLength + i] = src[i];
    }

    dest[destLength + i] = '\0';
}

