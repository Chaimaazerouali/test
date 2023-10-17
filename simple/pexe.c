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
int x, y;
char inCopy[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;
if (data->input_line == NULL)
return;
bufferAdd(inCopy, data->input_line);
for (x = 0; inCopy[x]; x++)
{
if (inCopy[x] == '#')
{
inCopy[x--] = '\0'; }
else if (inCopy[x] == '$' && inCopy[x + 1] == '?')
{
inCopy[x] = '\0';
convertLongToString(errno, expansion, 10);
bufferAdd(inCopy, expansion);
bufferAdd(inCopy, data->input_line + x + 2); }
else if (inCopy[x] == '$' && inCopy[x + 1] == '$')
{
inCopy[x] = '\0';
convertLongToString(getpid(), expansion, 10);
bufferAdd(inCopy, expansion);
bufferAdd(inCopy, data->input_line + x + 2); }
else if (inCopy[x] == '$' && (inCopy[x + 1] == ' ' || inCopy[x + 1] == '\0'))
continue;
else if (inCopy[x] == '$')
{
for (y = 1; inCopy[x + y] && inCopy[x + y] != ' '; y++)
{
expansion[y - 1] = inCopy[x + y]; }
temp = getEnvironmentVariable(expansion, data);
inCopy[x] = '\0';
expansion[0] = '\0';
bufferAdd(expansion, inCopy + x + y);
temp ? bufferAdd(inCopy, temp) : 1;
bufferAdd(inCopy, expansion); }
}
if (!strCompare(data->input_line, inCopy, 0))
{
free(data->input_line);
data->input_line = strDuplicate(inCopy); }
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
int x1, x2, wasExpanded = 0;
char inputCopy[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

if (data->input_line == NULL)
return;

bufferAdd(inputCopy, data->input_line);

for (x1 = 0; inputCopy[x1]; x1++)
{
for (x2 = 0; inputCopy[x1 + x2] && inputCopy[x1 + x2] != ' '; x2++)
{
expansion[x2] = inputCopy[x1 + x2];
}
expansion[x2] = '\0';
temp = getAliasValue(data, expansion);

if (temp)
{
expansion[0] = '\0';
bufferAdd(expansion, inputCopy + x1 + x2);
inputCopy[x1] = '\0';
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
int len, ix;

len = strLength(dest);
for (ix = 0; src[ix]; ix++)
{
dest[len + ix] = src[ix];
}
dest[len + ix] = '\0';
return (len + ix);
}

