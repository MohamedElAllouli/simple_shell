#include "main.h"
/**
 * len_list - get length of linked list
 * @head: head of list
 * Return: size of list
 */
size_t len_list(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}
/**
 * to_strings_list - get string list
 * @head: hrad of list
 * Return: array of strings
 */
char **to_strings_list(list_t *head)
{
	list_t *node = head;
	size_t i = len_list(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}
/**
 * list_print - prints elements of list
 * @head: head of list
 * Return: size of list
 */
size_t list_print(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(number_toconvert(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}
/**
 * node_begin_with - returns node whose string starts w
 * @head: head of list
 * @p_fix: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_begin_with(list_t *head, char *p_fix, char c)
{
	char *p = NULL;

	while (head)
	{
		p = starts_with(head->str, p_fix);
		if (p && ((c == -1) || (*p == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}
/**
 * get_index_node - get the index of a node
 * @head: pointer to list head
 * @n: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_index_node(list_t *head, list_t *n)
{
	size_t i = 0;

	while (head)
	{
		if (head == n)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
