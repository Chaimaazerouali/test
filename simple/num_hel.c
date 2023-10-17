#include "sheel.h"

/**
* convertLongToString -  Converts a number to a string representation.
* @num: The number to be converted to a string.
* @result: The buffer to save the number as a string.
* @base: The base for number conversion (e.g., 10 for decimal, 16 for hex).
*
* Return: Nothing.
*/
void convertLongToString(long num, char *result, int base)
{
int idx = 0, isNegative = 0;
long q = num;
char digits[] = "0123456789abcdef";

if (q == 0)
result[idx++] = '0';

if (result[0] == '-')
isNegative = 1;

while (q)
{
if (q < 0)
result[idx++] = digits[-(q % base)];
else
result[idx++] = digits[q % base];
q /= base;
}
if (isNegative)
result[idx++] = '-';

result[idx] = '\0';
strReverse(result);
}

/**
* parseInt - Converts a string to an integer.
* @str: Pointer to the source string.
* Return: The int value of the str or 0 if the string is not a valid integer.
*/
int parseInt(char *str)
{
int sign = 1;
unsigned int num = 0;

while (!('0' <= *str && *str <= '9') && *str != '\0')
{
if (*str == '-')
sign *= -1;
if (*str == '+')
sign *= +1;
str++;
}

while ('0' <= *str && *str <= '9'
&& *str != '\0')
{
num = (num * 10) + (*str - '0');
str++;
}
return (num *sign);
}

/**
* countCharacterOccurrences -  Counts the occurrences of a specific char a str.
* @str: Pointer to the source string.
* @charToCount: Pointer to a str containing char to be counted(single char).
*
* Return: The count of the specified character in the string.
*/
int countCharacterOccurrences(char *str, char *charToCount)
{
int idx = 0, count = 0;

for (; str[idx]; idx++)
{
if (str[idx] == charToCount[0])
count++;
}
return (count);
}

