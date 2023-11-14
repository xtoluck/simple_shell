#include "shell.h"

/**
 * interactive -This returns true if [given] shell is in an interactive mode.
 *  * @info: This is the [given] struct address
 * Return: This returns 1 if it's in interactive mode, then 0 if otherwise.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - This checks if a [given] character is a delimeter.
 * @c: This is the [particular character to actually check.
 * @delim: This is the [given] delimeter string.
 * Return: This returns 1 if true, or/and 0 if false. i.e if not true.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - This checks for [particular] alphabetic character
 *@c: This is the [given] character to input
 *Return: This returns 1 if c is alphabetic, and then  0 if otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - This converts a [particular] string to a [given]  integer
 *@s: This is the [given] string to be converted
 *Return:This returns 0 if no numbers in string, converted number if otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
