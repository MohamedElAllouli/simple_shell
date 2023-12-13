#include "main.h"
/**
 * buf_input - buffers chained commands
 * @f: structur
 * @b: address of buffer
 * @l: address of len var
 * Return:  readed bytes
 */
ssize_t buf_input(info_t *f, char **b, size_t *l)
{
	ssize_t r = 0;
	size_t l_p = 0;

	if (!*l)
	{
		free(*b);
		*b = NULL;
		signal(SIGINT, sig_int_Handler);
#if USE_GETLINE
		r = getline(b, &l_p, stdin);
#else
		r = get_line(f, b, &l_p);
#endif
		if (r > 0)
		{
			if ((*b)[r - 1] == '\n')
			{
				(*b)[r - 1] = '\0';
				r--;
			}
			f->linecount_flag = 1;
			delete_comments(*b);
			history_build_list(f, *b, f->histcount++);
			{
				*l = r;
				f->cmd_buf = b;
			}
		}
	}
	return (r);
}
/**
 * get_input - get  line minus the newline
 * @f: structur
 * Return: bytes read
 */
ssize_t get_input(info_t *f)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(f->arg), *p;

	_putchar(BUF_FLUSH);
	r = buf_input(f, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;
		chain_check(f, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(f, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			f->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (r);
}
/**
 * buf_read - reads a buffer
 * @f: parameter struct
 * @b: buffer
 * @s: size
 * Return: r
 */
ssize_t buf_read(info_t *f, char *b, size_t *s)
{
	ssize_t r = 0;

	if (*s)
		return (0);
	r = read(f->readfd, b, READ_BUF_SIZE);
	if (r >= 0)
		*s = r;
	return (r);
}
/**
 * get_line - gets next line of input
 * @f:  structur
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @l: size of preallocated ptr buffer if not NULL
 * Return: size
 */
int get_line(info_t *f, char **ptr, size_t *l)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && l)
		s = *l;
	if (i == len)
		i = len = 0;

	r = buf_read(f, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (l)
		*l = s;
	*ptr = p;
	return (s);
}
/**
 * sig_int_Handler - blocks ctrl c
 * @num_sign: the signal number
 */
void sig_int_Handler(__attribute__((unused))int num_sign)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
