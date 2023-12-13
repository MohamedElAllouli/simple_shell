#include "main.h"

/**
 * _memoryset - stack memory with a constant byte
 *@str: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the number of bytes to be filled
 *Return: string
 */
char *_memoryset(char *str, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		str[j] = b;
	return (str);
}
/**
 * f_free - free array of string
 * @ss: string of strings
 */
void f_free(char **ss)
{
	char **s = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(s);
}
/**
 * _realloc - reallocates a block of memory
 * @p: previous mallocated memory
 * @previous_size: byte size of previous block
 * @newsize: byte size of new block
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *p, unsigned int previous_size, unsigned int newsize)
{
	char *pt;

	if (!p)
		return (malloc(newsize));
	if (!newsize)
		return (free(p), NULL);
	if (newsize == previous_size)
		return (p);

	pt = malloc(newsize);
	if (!pt)
		return (NULL);

	previous_size = previous_size < newsize ? previous_size : newsize;
	while (previous_size--)
		pt[previous_size] = ((char *)p)[previous_size];
	free(p);
	return (pt);
}
