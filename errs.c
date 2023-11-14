#include "shell.h"

/**
 *_eputs - This prints a [particular] input string
 * @str: This is the [particular] string to be printed
 * Return: This returns nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - This writes the [particular] character c to the [given] stderr
 * @c: This is the [particular] character to print or write tothe stderr
 * Return: This returns on success 1.
 * On error, it returns -1, and [particular] error number is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - This writes the character c to a [given] file discriptor, fd
 * @c: This is the [particular] character to print or display
 * @fd: This is the [particular] filedescriptor to write to
 * Return: This returns success 1.
 * On error, it returns -1, and [particular] err number is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - This wites or prints a [given] input string
 * @str: This is the [given] string to be printed
 * @fd: This is the filedescriptor to write or print to.
 * Return: This is the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
