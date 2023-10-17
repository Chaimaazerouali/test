#include "sheel.h"

/**
* custom_getline - Read and process input commands from the file descriptor.
* @ shelldata: A pointer to the shell data.
* @return The length of the input line read, or -1 if there are no more cmds.
*/
int custom_getline(CustomShellData *shelldata)
{
char buff[BUFFER_SIZE] = {'\0'};
static char *arycmd[10] = {NULL};
static char aryops[10] = {'\0'};
ssize_t bytes_read;
int i = 0;

if (!arycmd[0] || (aryops[0] == '&' && errno != 0) ||
(aryops[0] == '|' && errno == 0))
{
for (i = 0; arycmd[i]; i++)
{
free(arycmd[i]);
arycmd[i] = NULL;
}

bytes_read = read(shelldata->file_descriptor, &buff, BUFFER_SIZE - 1);
if (bytes_read == 0)
return (-1);

i = 0;
do {
arycmd[i] = strDuplicate(customStrtok(i ? NULL : buff, "\n;"));
i = check_logical_operators(arycmd, i, aryops);
} while (arycmd[i++]);
}

shelldata->input_line = arycmd[0];
for (i = 0; arycmd[i]; i++)
{
arycmd[i] = arycmd[i + 1];
aryops[i] = aryops[i + 1];
}

return (strLength(shelldata->input_line));
}

/**
* check_logical_operators - Separate commands based on logical operators.
* @arycmd: An array of command strings.
* @i: The current index in the array of command strings.
* @aryops: An array of logical operators
* @return The updated index for the next command.
*/
int check_logical_operators(char *arycmd[], int i, char aryops[])
{
char *temp = NULL;
int jx;

for (jx = 0; arycmd[i] != NULL  && arycmd[i][jx]; jx++)
{
if (arycmd[i][jx] == '&' && arycmd[i][jx + 1] == '&')
{
temp = arycmd[i];
arycmd[i][jx] = '\0';
arycmd[i] = strDuplicate(arycmd[i]);
arycmd[i + 1] = strDuplicate(temp + jx + 2);
i++;
aryops[i] = '&';
free(temp);
jx = 0;
}
if (arycmd[i][jx] == '|' && arycmd[i][jx + 1] == '|')
{
temp = arycmd[i];
arycmd[i][jx] = '\0';
arycmd[i] = strDuplicate(arycmd[i]);
arycmd[i + 1] = strDuplicate(temp + jx + 2);
i++;
aryops[i] = '|';
free(temp);
jx = 0;
}
}
return (i);
}

