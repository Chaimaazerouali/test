#include "sheel.h"

/**
* strLength - returns the length of a string.
* @str: pointer to the string.
* Return: length of the string.
*/
int strLength(char *str)
{
int length = 0;

if (str == NULL)
return (0);

while (str[length] != '\0')
{
length++;
}
return (length);
}

/**
* strDuplicate - duplicates a string.
* @str: String to be copied.
* Return: pointer to the duplicated string.
*/
char *strDuplicate(char *str)
{
char *result;
int length, i;

if (str == NULL)
return (NULL);

length = strLength(str) + 1;
result = malloc(sizeof(char) * length);

if (result == NULL)
{
errno = (ENOMEM);
perror("Error");
return (NULL);
}

for (i = 0; i < length; i++)
{
result[i] = str[i];
}

return (result);
}

/**
* strCompare - Compare two strings.
* @str1: String one, or the shorter.
* @str2: String two, or the longer.
* @count: Number of characters to be compared, 0 if infinite.
* Return: 1 if the strings are equals, 0 if the strings are different.
*/
int strCompare(char *str1, char *str2, int count)
{
int iterator;

if (str1 == NULL && str2 == NULL)
return (1);

if (str1 == NULL || str2 == NULL)
return (0);

if (count == 0) /* Infinite length */
{
if (strLength(str1) != strLength(str2))
return (0);
for (iterator = 0; str1[iterator]; iterator++)
{
if (str1[iterator] != str2[iterator])
return (0);
}
return (1);
}
else /* If there is a number of characters to be compared*/
{
for (iterator = 0; iterator < count; iterator++)
{
if (str1[iterator] != str2[iterator])
return (0);
}
return (1);
}
}

/**
* strConcat - Concatenates two strings.
* @str1: First string to be concatenated.
* @str2: Second string to be concatenated.
* Return: Pointer to the concatenated string.
*/
char *strConcat(char *str1, char *str2)
{
char *result;
int length1 = 0, length2 = 0;

if (str1 == NULL)
str1 = "";
length1 = strLength(str1);

if (str2 == NULL)
str2 = "";
length2 = strLength(str2);

result = malloc(sizeof(char) * (length1 + length2 + 1));
if (result == NULL)
{
errno = ENOMEM;
perror("Error");
return (NULL);
}


for (length1 = 0; str1[length1] != '\0'; length1++)
{
result[length1] = str1[length1];
}
free(str1);


for (length2 = 0; str2[length2] != '\0'; length2++)
{
result[length1] = str2[length2];
length1++;
}

result[length1] = '\0';
return (result);
}

/**
* strReverse - Reverses a string.
* @str: pointer to the string.
* Return: void.
*/
void strReverse(char *str)
{
int i = 0, length = strLength(str) - 1;
char hold;

while (i < length)
{
hold = str[i];
str[i++] = str[length];
str[length--] = hold;
}
}

