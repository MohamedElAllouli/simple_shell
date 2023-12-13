#include "main.h"
/**
 * **str_tow1 - cut a string into words.
 * @str: the  string
 * @d: delimeter string
 * Return: array of string
 */
char **str_tow1(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_de_lim(str[i], d) && (is_de_lim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_de_lim(str[i], d))
			i++;
		k = 0;
		while (!is_de_lim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
/**
 * **str_tow2 - splits a string into words
 * @s: input string
 * @d: the delimeter
 * Return: array of strings
 */
char **str_tow2(char *s, char d)
{
	int i, j, k, m, number_w = 0;
	char **r;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
		if ((s[i] != d && s[i + 1] == d) ||
		    (s[i] != d && !s[i + 1]) || s[i + 1] == d)
			number_w++;
	if (number_w == 0)
		return (NULL);
	r = malloc((1 + number_w) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < number_w; j++)
	{
		while (s[i] == d && s[i] != d)
			i++;
		k = 0;
		while (s[i + k] != d && s[i + k] && s[i + k] != d)
			k++;
		r[j] = malloc((k + 1) * sizeof(char));
		if (!r[j])
		{
			for (k = 0; k < j; k++)
				free(r[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			r[j][m] = s[i++];
		r[j][m] = 0;
	}
	r[j] = NULL;
	return (r);
}
