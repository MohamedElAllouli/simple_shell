#include "main.h"
/**
 * _my_history - print the history list
 * @f: Structure of informaion
 *  Return: Always 0
 */
int _my_history(info_t *f)
{
	list_print(f->history);
	return (0);
}
/**
 * alias_unset - sets alias to string
 * @f: struct
 * @s: the string
 * Return: 0 on success,
 */
int alias_unset(info_t *f, char *s)
{
	char *p, c;
	int r;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	r = remove_node_at_index(&(f->alias),
		get_index_node(f->alias, node_begin_with(f->alias, s, -1)));
	*p = c;
	return (r);
}

/**
 * alias_set - sets alias to string
 * @f:structur
 * @s: string alias
 * Return: 0 on success
 */
int alias_set(info_t *f, char *s)
{
	char *p;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (alias_unset(f, s));

	alias_unset(f, s);
	return (add_node_at_end(&(f->alias), s, 0) == NULL);
}

/**
 * _alias_print - print an alias string
 * @node: the alias node
 * Return: 0 on success
 */
int _alias_print(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _my_alias - the alias builtin
 * @f: Structure containing potential arguments.
 *  Return:  0 onsuccess
 */
int _my_alias(info_t *f)
{
	int i = 0;
	char *p = NULL;
	list_t *n = NULL;

	if (f->argc == 1)
	{
		n = f->alias;
		while (n)
		{
			_alias_print(n);
			n = n->next;
		}
		return (0);
	}
	for (i = 1; f->argv[i]; i++)
	{
		p = _strchr(f->argv[i], '=');
		if (p)
			alias_set(f, f->argv[i]);
		else
			_alias_print(node_begin_with(f->alias, f->argv[i], '='));
	}
	return (0);
}
