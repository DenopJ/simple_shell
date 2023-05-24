#include "shell.h"

/**
 * _erratoi - converts string to integer
 * @s: parameter
 *
 * Return: 0 if string, -1 on error
 */
int _erratoi(char *s)
{
	int x = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (x = 0;  s[x] != '\0'; x++)
	{
		if (s[x] >= '0' && s[x] <= '9')
		{
			res = res * 10;
			res = res + (s[x] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_z - function prints base 10
 * @input: first parametr
 * @fd: second parameter
 *
 * Return: character number
 */
int print_z(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int x;
	int count = 0;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			__putchar('0' + curr / x);
			count++;
		}
		curr = curr % x;
	}
	__putchar('0' + curr);
	count++;

	return (count);
}

/**
 * convert_number - function is a converter
 * @num: first parameter
 * @base: second parameter
 * @flags: third parameter
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *arr;
	static char buff[50];
	char s = 0;
	char *ptr;
	unsigned long x = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		x = -num;
		s = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[x % base];
		x /= base;
	} while (x != 0);

	if (s)
		*--ptr = s;
	return (ptr);
}

/**
 * print_error - prints error message
 * @info: first paramter
 * @estr: second parameter
 *
 * Return: void
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_z(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * remove_comments - function replaces '#' with '\0'
 * @buf: parameter
 *
 * Return: void
 */
void remove_comments(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}
