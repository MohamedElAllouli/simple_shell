#include "main.h"
/**
 * e_puts - prints an input string
 * @s: string
 */
void e_puts(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		e_putchar(s[i]);
		i++;
	}
}
/**
 * e_putchar - writes the character c to std err
 * @c: The character to print
 * Return: On success 1. or -1 in error
 */
int e_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * _put_fd - writes the character  to given filedescriptor
 * @c: character to print
 * @fd: filedescriptor to write to
 * Return: On success 1 or -1 in error
 */
int _put_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_puts_fd - display an input string
 * @s: the string
 * @fd: filedescriptor to write to
 * Return: number of chars put
 */
int _puts_fd(char *s, int fd)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += _put_fd(*s++, fd);
	}
	return (i);
}
