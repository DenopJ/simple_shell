#include "shell.h"

/**
 * _memset - puts constant byte into memory
 * @s: first parameter
 * @b: second parameter
 * @n: third parameter
 *
 * Return: pointer
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int x;

	for (x = 0; x < n; x++)
		s[x] = b;
	return (s);
}

/**
 * _realloc - reallocates memory block
 * @ptr: first parameter
 * @old_size: second parameter
 * @new_size: third parameter
 *
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *ptn;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	ptn = malloc(new_size);
	if (!ptn)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		ptn[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (ptn);
}

/**
 * ffree - frees string
 * @pp: parameter
 *
 * Return: void
 */
void ffree(char **pp)
{
	char **s = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(s);
}
