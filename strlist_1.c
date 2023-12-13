#include "main.h"
/**
 * node_add - add  node to the start of the list
 * @head: head of list
 * @s: string  field of node
 * @n: node  used by history
 * Return: size of list
 */
list_t *node_add(list_t **head, const char *s, int n)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memoryset((void *)new_head, 0, sizeof(list_t));
	new_head->num = n;
	if (s)
	{
		new_head->str = _strdup(s);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}
/**
 * add_node_at_end - adds a node to the end of the list
 * @head: head of list
 * @s: string of node
 * @n: node sed by history
 * Return: size of list
 */
list_t *add_node_at_end(list_t **head, const char *s, int n)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memoryset((void *)new_node, 0, sizeof(list_t));
	new_node->num = n;
	if (s)
	{
		new_node->str = _strdup(s);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * list_print_str - print string of linked list
 * @head: first node
 * Return: size of list
 */
size_t list_print_str(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}
/**
 * remove_node_at_index - remove node at given index
 * @head: head of list
 * @index: index of node to remove
 * Return: 1 on success
 */
int remove_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *p_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			p_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		p_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * list_free - frees all nodes of a list
 * @head: head of list
 */
void list_free(list_t **head)
{
	list_t *node, *next_node, *head_p;

	if (!head || !*head)
		return;
	head_p = *head;
	node = head_p;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head = NULL;
}
