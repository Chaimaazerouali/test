#include "sheel.h"

/**
* customTokenizer - function separates the string using a designated delimiter.
* @data: A pointer to the program's data.
* Return: An array of the different parts of the string.
*/
void customTokenizer(CustomShellData *data)
{
char *customDelimit = " \t";
int i, j, tokenCounter = 2, stLength;

stLength = strLength(data->input_line);
if (stLength)
{
if (data->input_line[stLength - 1] == '\n')
data->input_line[stLength - 1] = '\0';
}

for (i = 0; data->input_line[i]; i++)
{
for (j = 0; customDelimit[j]; j++)
{
if (data->input_line[i] == customDelimit[j])
tokenCounter++;
}
}

data->tokens = malloc(tokenCounter *sizeof(char *));
if (data->tokens == NULL)
{
perror(data->program_name);
exit(errno);
}
i = 0;
data->tokens[i] = strDuplicate(customStrtok(data->input_line, customDelimit));
data->command_name = strDuplicate(data->tokens[0]);
while (data->tokens[i++])
{
data->tokens[i] = strDuplicate(customStrtok(NULL, customDelimit));
}
}

