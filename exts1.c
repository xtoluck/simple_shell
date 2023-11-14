#include "shell.h"

/**
 **_strncpy - This copies a [given] string
 *@dest: This is the [given] destination string to be copied to
 *@src:This is the [given] source string
 *@n:This is the [particular] amount of characters to be copied
 *Return:This returns the concatenated or combined string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - This concatenates two [given] strings
 *@dest: This is the first [given] string
 *@src: This is the second [given] string
 *@n: This is the [particular] bytes to be maximally or [optimally] used
 *Return: This returns the [given] concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - This locates a [particular] character in a
 *	[set of a particular]  string
 *@s:This is the [given] string to be parsed
 *@c: This is the [given] character to look out for
 *Return: This is (s) a pointer to the [given] memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
