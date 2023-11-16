#include "shell.h"

/**
 * lists_lens - This function  determines length of linked list
 * @h: It is a pointer to first node
 *
 * Return: size of list
 */
size_t lists_lens(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * lists_to_string - This function returns an array of strings of the list->str
 * @head: It is a pointer to first node
 *
 * Return: array of strings
 */
char **lists_to_string(list_t *head)
{
	list_t *node = head;
	size_t a = lists_lens(head), b;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * prints_lists - This function prints all elements of a list_t linked list
 * @h: It is a pointer to first node
 *
 * Return: size of list
 */
size_t prints_lists(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * nodes_start_with - This function returns node
 * whose string starts with prefix
 * @node: It is a pointer to list head
 * @prefix: This is string to match
 * @c: Thi is the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nodes_start_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = started_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * gets_nodes_indexes - This function gets the index of a node
 * @head: It is a pointer to list head
 * @node: It is pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t gets_nodes_indexes(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}
