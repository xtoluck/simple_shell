#include "shell.h"

/**
 * find_strlen - This function returns the length of a string
 * @s: Thi is the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}

/**
 * Find_strcmp - This function performs lexicogarphic
 * comparison of two strangs.
 * @s1: This is the first strang
 * @s2: This is the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int find_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * started_with - This function checks if needle starts with haystack
 * @haystack: This is the string to search
 * @needle: This is the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *started_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * find_strcat - This function concatenates two strings
 * @dest: This is the destination buffer
 * @src: Thi is the source buffer
 *
 * Return: pointer to destination buffer
 */
char *find_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
