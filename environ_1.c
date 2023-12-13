#include "main.h"
/**
 * _my_env - display the current environment
 * @f: Structure of information
 * Return: Always 0
 */
int _my_env(info_t *f)
{
	list_print_str(f->env);
	return (0);
}
/**
 * _envget - the value of an environ variable
 * @f: Structure of information
 * @n: name of environ
 * Return: string
 */
char *_envget(info_t *f, const char *n)
{
	list_t *node = f->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, n);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}
/**
 * _my_set_env - Initialize a new environment
 * @f: Structure of information
 *  Return: Always 0
 */
int _my_set_env(info_t *f)
{
	if (f->argc != 3)
	{
		e_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_set_env(f, f->argv[1], f->argv[2]))
		return (0);
	return (1);
}
/**
 * _my_unset_env - delete an environment variable
 * @f: Structure of information
 *  Return: Always 0
 */
int _my_unset_env(info_t *f)
{
	int i;

	if (f->argc == 1)
	{
		e_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= f->argc; i++)
		_unset_env(f, f->argv[i]);

	return (0);
}
/**
 * populate_list_env - list of populate environ
 * @f: Structure of information
 * Return: Always 0
 */
int populate_list_env(info_t *f)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_at_end(&node, environ[i], 0);
	f->env = node;
	return (0);
}
