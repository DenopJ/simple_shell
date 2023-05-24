#include "shell.h"

/**
 * _putfd - prints character to given fd
 * @c: first parameter
 * @fd: second parameter
 *
 * Return: Always 1 (success). -1 (error)
 */
int _putfd(char c, int fd)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fd, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/**
 * _eputchar - prints character to stderr
 * @c: parameter
 *
 * Return: Always 1 (success), -1 (error)
 */
int _eputchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/**
 * _eputs - prints a string from inpu
 * @str: parameter
 *
 * Return: void
 */
void _eputs(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_eputchar(str[x]);
		x++;
	}
}

/**
 * _putsfd - prints an input string
 * @str: first parameter
 * @fd: second parameter
 *
 * Return: number of chars
 */
int _putsfd(char *str, int fd)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x = x + _putfd(*str++, fd);
	}
	return (x);
}
