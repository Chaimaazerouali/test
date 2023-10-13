include "shell.h"

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

    return aliasFound ? 0 : 1;
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
        return NULL;

    aliasNameLength = strLength(aliasName);

    for (i = 0; data->alias_list[i]; i++)
    {
        if (strCompare(aliasName, data->alias_list[i], aliasNameLength) &&
            data->alias_list[i][aliasNameLength] == '=')
        {
            return data->alias_list[i] + aliasNameLength + 1;
        }
    }

    return NULL;
}

/**
 * setAlias - Adds or overrides an alias.
 * @aliasString: Alias to be set in the form (name='value').
 * @data: Struct for the program's data.
 * Return: 0 if success, 1 otherwise.
 */
int setAlias(char *aliasString,CustomShellData *data)
{
    char *aliasName, *aliasValue;
    int aliasNameLength;

    if (aliasString == NULL || data->alias_list == NULL)
        return 1;

    aliasName = strtok(aliasString, "=");
    if (!aliasName)
        return 1;

    aliasNameLength = strLength(aliasName);
    aliasValue = strtok(NULL, "");

    if (!aliasValue)
        aliasValue = ""; /* If no value provided, set it to an empty string */

    for (int i = 0; data->alias_list[i]; i++)
    {
        if (strCompare(aliasName, data->alias_list[i], aliasNameLength) &&
            data->alias_list[i][aliasNameLength] == '=')
        {
            /* If the alias already exists, update its value*/
            snprintf(data->alias_list[i], sizeof(data->alias_list[i]), "%s=%s", aliasName, aliasValue);
            return 0;
        }
    }

    // If the alias doesn't exist, create a new one
    if (snprintf(data->alias_list[data->alias_count], sizeof(data->alias_list[data->alias_count]),
                  "%s=%s", aliasName, aliasValue) >= sizeof(data->alias_list[data->alias_count]))
    {
        // The alias is too long to fit into the allocated memory, handle this case accordingly
       return 1;
    }

    data->alias_count++;
    return 0;
}

