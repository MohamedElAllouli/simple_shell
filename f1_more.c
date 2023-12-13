#include "main.h"

/**
 * is_interactive - test if shell is interactive mode
 * @f: struct address
 * Return: 1 on success
 */
int is_interactive(info_t *f)
{
	return (isatty(STDIN_FILENO) && f->readfd <= 2);
}
/**
 * is_de_lim - teste if character is a delimeter
 * @c: char to check
 * @d: delimeter string
 * Return: 1 on success, 0 if false
 */
int is_de_lim(char c, char *d)
{
	while (*d)
		if (*d++ == c)
			return (1);
	return (0);
}
/**
 *_isalpha - check of alphabetic character
 *@c: character
 *Return: 1 on success
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 *_atoi - convert a string to an integer
 *@str: the string to conver
 *Return: 0 on success
 */
int _atoi(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
