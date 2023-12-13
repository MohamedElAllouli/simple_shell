#include "main.h"
/**
 * environ_get - get the stringcopy of environ
 * @f: Structure of information
 * Return: Always 0
 */
char **environ_get(info_t *f)
{
	if (!f->environ || f->env_changed)
	{
		f->environ = to_strings_list(f->env);
		f->env_changed = 0;
	}
	return (f->environ);
}
/**
 * _unset_env - delete an environment variable
 * @f: Structure of information
 * @va: var property od string environ
 *  Return: 1 on delete, 0 otherwise
 */
int _unset_env(info_t *f, char *va)
{
	list_t *node = f->env;
	size_t i = 0;
	char *p;

	if (!node || !va)
		return (0);

	while (node)
	{
		p = starts_with(node->str, va);
		if (p && *p == '=')
		{
			f->env_changed = remove_node_at_index(&(f->env), i);
			i = 0;
			node = f->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (f->env_changed);
}

/**
 * _set_env - Initialize or modify a new environment variabl
 * @f: Structure of information
 * @v: string env var property
 * @va: string env var value
 *  Return: Always 0
 */
int _set_env(info_t *f, char *v, char *va)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!v || !va)
		return (0);
	buf = malloc(_strlen(v) + _strlen(v) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, v);
	_strcat(buf, "=");
	_strcat(buf, va);
	node = f->env;
	while (node)
	{
		p = starts_with(node->str, v);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			f->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_at_end(&(f->env), buf, 0);
	free(buf);
	f->env_changed = 1;
	return (0);
}
