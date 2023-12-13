#include "main.h"
/**
 * bfree - free a pointer
 * @p: pointer to free
 * Return: 1 if success
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
