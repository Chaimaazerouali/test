#include "sheel.h"
/**
* showAliases - Prints aliases to the standard output.
* @data: Struct for the program's data.
* @aliasName: Name of the alias to be printed. NULL to print all aliases.
* Return: 0 if success, 1 otherwise.
*/
int showAliases(CustomShellData *data, char *aliasName)
{
int i, aliasNameLength, aliasFound = 0;
if (data->alias_list)
{
aliasNameLength = strLength(aliasName);
for (i = 0; data->alias_list[i]; i++)
{
if (!aliasName || (strCompare(data->alias_list[i], aliasName, aliasNameLength)
&& data->alias_list[i][aliasNameLength] == '='))
{
char *aliasValue = strchr(data->alias_list[i], '=');
if (aliasValue)
{
aliasValue++; /* move pointer to the value after '='*/
printToStdout("'");
printToStdout(aliasValue);
printToStdout("'\n");
aliasFound = 1;
}
}
}
}

return (aliasFound ? 0 : 1);
}

/**
* getAliasValue - Gets the value of a specific alias.
* @data: Struct for the program's data.
* @aliasName: Name of the requested alias.
* Return: Pointer to the alias value if found, NULL otherwise.
*/
char *getAliasValue(CustomShellData *data, char *aliasName)
{
int i, aliasNameLength;

if (aliasName == NULL || data->alias_list == NULL)
return (NULL);

aliasNameLength = strLength(aliasName);

for (i = 0; data->alias_list[i]; i++)
{
if (strCompare(aliasName, data->alias_list[i], aliasNameLength) &&
data->alias_list[i][aliasNameLength] == '=')
{
return (data->alias_list[i] + aliasNameLength + 1);
}
}

return (NULL);
}


/**
* setAlias - Define or update an alias.
* @alias_string: The string containing the alias definition.
* @program_data: A structure containing program data.
* Return: 0 if successful, or another number if there's an issue.
*/
int setAlias(char *alias_string, CustomShellData *program_data)
{
int in, jx;
char alias_name[250] = {'0'}, *alias_value = NULL;

/* Validate the arguments */
if (alias_string == NULL || program_data->alias_list == NULL)
return (1);
/* Iterate through the alias string to find the '=' character */
for (in = 0; alias_string[in]; in++)
{
if (alias_string[in] != '=')
{
alias_name[in] = alias_string[in]; }
else
{
/* Search if the value of the alias is another alias */
alias_value = getAliasValue(program_data, alias_string + in + 1);
break; }
}
/* Iterate through the alias list and check for a match with the alias name */
for (jx = 0; program_data->alias_list[jx]; jx++)
{
if (strCompare(alias_name, program_data->alias_list[jx], in) &&
program_data->alias_list[jx][in] == '=')
{
/* If the alias already exists, free the previous one */
free(program_data->alias_list[jx]);
break; }
}
/* Add the alias */
if (alias_value)
{
bufferAdd(alias_name, "=");
bufferAdd(alias_name, alias_value);
program_data->alias_list[jx] = strDuplicate(alias_string);
}
else
{
/* If the alias does not exist, create a new one */
program_data->alias_list[jx] = strDuplicate(alias_string); }
return (0); }
