#include "shell.h"

/**
 * bfree - freeing pointer from address
 * @ptr: pointer address
 *
 * Return: 1 success 0 failure
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

