#include "main.h"
/**
 * _err_atoi - converts a string to  integer
 * @str: the string to be converted
 * Return: 0 on succss
 */
int _err_atoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
/**
 * error_print - prints error message
 * @f: the information struct
 * @strer: string containing error type
 * Return: 0 on success
 */
void error_print(info_t *f, char *strer)
{
	e_puts(f->fname);
	e_puts(": ");
	d_print(f->line_count, STDERR_FILENO);
	e_puts(": ");
	e_puts(f->argv[0]);
	e_puts(": ");
	e_puts(strer);
}
/**
 * d_print -print decimal number
 * @value: the input
 * @fd: filedescriptor to write in
 * Return: number of characters printed
 */
int d_print(int value, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs, current;

	if (fd == STDERR_FILENO)
		__putchar = e_putchar;
	if (value < 0)
	{
		_abs = -value;
		__putchar('-');
		count++;
	}
	else
		_abs = value;
	current = _abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}
/**
 *number_toconvert - converter function
 * @n: number to convert
 * @b: base of number
 * @f: argument flags
 * Return: string
 */
char *number_toconvert(long int n, int b, int f)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *p;
	unsigned long num = n;

	if (!(f & CONVERT_UNSIGNED) && n < 0)
	{
		num = -n;
		sign = '-';
	}
	array = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';
	do	{
		*--p = array[num % b];
		num /= b;
	} while (num != 0);
	if (sign)
		*--p = sign;
	return (p);
}
/**
 * delete_comments - replace comment
 * @s: string to modify
 * Return: 0 on success
 */
void delete_comments(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		if (s[i] == '#' && (!i || s[i - 1] == ' '))
		{
			s[i] = '\0';
			break;
		}
}
