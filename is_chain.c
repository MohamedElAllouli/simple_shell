#include "main.h"
/**
 * is_chain -check if caracter in buffer
 * @f: structure of information
 * @buf: buffer
 * @p: current position in buffer
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *f, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		f->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		f->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		f->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}
/**
 * chain_check - checks chain
 * @f: structure of information
 * @buf: buffer
 * @p: current position in buffer
 * @i: starting position in buffer
 * @l: length of buffer
 */
void chain_check(info_t *f, char *buf, size_t *p, size_t i, size_t l)
{
	size_t j = *p;

	if (f->cmd_buf_type == CMD_AND)
	{
		if (f->status)
		{
			buf[i] = 0;
			j = l;
		}
	}
	if (f->cmd_buf_type == CMD_OR)
	{
		if (!f->status)
		{
			buf[i] = 0;
			j = l;
		}
	}
	*p = j;
}
/**
 * alias_replace - replaces  aliases in string
 * @f: structure of information
 * Return: 1 if replaced, 0 otherwise
 */
int alias_replace(info_t *f)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_begin_with(f->alias, f->argv[0], '=');
		if (!node)
			return (0);
		free(f->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		f->argv[0] = p;
	}
	return (1);
}
/**
 * vars_replace - replaces vars in string
 * @f: structure of information
 * Return: 1 if replaced, 0 otherwise
 */
int vars_replace(info_t *f)
{
	int i = 0;
	list_t *node;

	for (i = 0; f->argv[i]; i++)
	{
		if (f->argv[i][0] != '$' || !f->argv[i][1])
			continue;

		if (!_strcmp(f->argv[i], "$?"))
		{
			string_replace(&(f->argv[i]),
				_strdup(number_toconvert(f->status, 10, 0)));
			continue;
		}
		if (!_strcmp(f->argv[i], "$$"))
		{
			string_replace(&(f->argv[i]),
				_strdup(number_toconvert(getpid(), 10, 0)));
			continue;
		}
		node = node_begin_with(f->env, &f->argv[i][1], '=');
		if (node)
		{
			string_replace(&(f->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		string_replace(&f->argv[i], _strdup(""));

	}
	return (0);
}
/**
 * string_replace - replaces string
 * @o:  old string
 * @n: new string
 * Return: 1 if replaced, 0 otherwise
 */
int string_replace(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
