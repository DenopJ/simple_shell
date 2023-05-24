#include "shell.h"

/**
 * **strtow2 - splits a string into words
 * @str: first parameter
 * @d: second parameter
 *
 * Return: string pointer,  NULL (failure)
 */
char **strtow2(char *str, char d)
{
	int x, y, q, r;
	int num = 0;
	char **a;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
				    (str[x] != d && !str[x + 1]) || str[x + 1] == d)
			num++;
	if (num == 0)
		return (NULL);
	a = malloc((1 + num) * sizeof(char *));
	if (!a)
		return (NULL);
	for (x = 0, y = 0; y < num; y++)
	{
		while (str[x] != d && str[x] == d)
			x++;
		q = 0;
		while (str[x + q] != d && str[x + q] && str[x + q] != d)
			q++;
		a[y] = malloc((q + 1) * sizeof(char));
		if (!a[y])
		{
			for (q = 0; q < y; q++)
				free(a[q]);
			free(a);
			return (NULL);
		}
		for (r = 0; r < q; r++)
			a[y][r] = str[x++];
		a[y][r] = 0;
	}
	a[y] = NULL;
	return (a);
}

/**
 * **strtow - splits a string into words
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int x, y, q, r;
	int num = 0;
	char **a;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!ks_delim(str[x], d) && (ks_delim(str[x + 1], d) || !str[x + 1]))
			num++;

	if (num == 0)
		return (NULL);
	a = malloc((1 + num) * sizeof(char *));
	if (!a)
		return (NULL);
	for (x = 0, y = 0; y < num; y++)
	{
		while (ks_delim(str[x], d))
			x++;
		q = 0;
		while (!ks_delim(str[x + q], d) && str[x + q])
			q++;
		a[y] = malloc((q + 1) * sizeof(char));
		if (!a[y])
		{
			for (q = 0; q < y; q++)
				free(a[q]);
			free(a);
			return (NULL);
		}
		for (r = 0; r < q; r++)
			a[y][r] = str[x++];
		a[y][r] = 0;
	}
	a[y] = NULL;
	return (a);
}
