#include "main.h"

/**
 **_strncpy - copies a string
 *@d: destination string
 *@s: source string
 *@n: number of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *d, char *s, int n)
{
	int i, j;
	char *r = d;

	i = 0;
	while (s[i] != '\0' && i < n - 1)
	{
		d[i] = s[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (r);
}
/**
 **_strncat - concatenates two strings
 *@d: first string
 *@s: second string
 *@n: number of bytes to be maximally used
 *Return: string
 */
char *_strncat(char *d, char *s, int n)
{
	int i, j;
	char *r = d;

	i = 0;
	j = 0;
	while (d[i] != '\0')
		i++;
	while (s[j] != '\0' && j < n)
	{
		d[i] = s[j];
		i++;
		j++;
	}
	if (j < n)
		d[i] = '\0';
	return (r);
}
/**
 **_strchr - get a character in a string
 *@str: string parsed
 *@c: character to get
 *Return: string
 */
char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
