#include "shell.h"

/**
 **_strncat - concatenates strings
 *@dest: first parameter
 *@src: second parameter
 *@n: third parameter
 *
 *Return: string character
 */
char *_strncat(char *dest, char *src, int n)
{
	int x = 0, y = 0;
	char *str = dest;

	while (dest[x] != '\0')
		x++;
	while (y < n && src[y] != '\0')
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (n > y)
		dest[x] = '\0';
	return (str);
}

/**
 **_strchr - character finder in a string
 *@s first paramter
 *@c: second parameter
 *
 *Return: character
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 **_strncpy - copy string
 *@dest: first parameter
 *@src: second parameter
 *@n: third parameter
 *
 *Return: string character
 */
char *_strncpy(char *dest, char *src, int n)
{
	int x = 0, y;
	char *str = dest;

	while (x < n - 1 && src[x] != '\0')
	{
		dest[x] = src[x];
		x++;
	}
	if (n > x)
	{
		y = x;
		while (y < n)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (str);
}
