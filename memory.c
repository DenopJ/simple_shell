#include "shell.h"

/**
 * btfree - frees a pointer and NULLs address
 * @pntr: address of pointer to free
 * Return: 1 if freed, otherwise 0.
 */
int btfree(void **pntr)
{
	if (pntr && *pntr)
	{
		free(*pntr);
		*pntr = NULL;
		return (1);
	}
	return (0);
}
