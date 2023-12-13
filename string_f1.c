#include "main.h"
/**
 * _strlen - length of a string
 * @s: the string
 * Return: length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}
/**
 * _strcmp - compare two string.
 * @s1: the first strang
 * @s2: the second strang
 * Return: 0 if success
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * starts_with - checks if substring  starts with string to search
 * @s_sear: string to search
 * @sub_s: the substring to find
 * Return: address of next char of string
 */
char *starts_with(const char *s_sear, const char *sub_s)
{
	while (*sub_s)
		if (*sub_s++ != *s_sear++)
			return (NULL);
	return ((char *)s_sear);
}
/**
 * _strcat - concatenates two strings
 * @d: the destination buffer
 * @s: the source buffer
 * Return: string
 */
char *_strcat(char *d, char *s)
{
	char *r = d;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (r);
}
