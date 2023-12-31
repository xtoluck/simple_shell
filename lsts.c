#include "shell.h"

/**
 * adds_nodes - This function adds a node to the start of the list
 * @head: This represents the address of pointer to head node
 * @str: This represents the str field of node
 * @num: This is the node index used by history
 *
 * Return: size of list
 */
list_t *adds_nodes(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
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
 * adds_nodes_ended - The function adds a node to the end of the list
 * @head: This is address of pointer to head node
 * @str: This is str field of node
 * @num: This is node index used by history
 *
 * Return: size of list
 */
list_t *adds_nodes_ended(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
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
 * prints_lists_string - This function prints only the str element of a
 * list_t linked list
 * @h: This is pointer to first node
 *
 * Return: size of list
 */
size_t prints_lists_string(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * deletes_nodes_at_indexes - This function deletes node at given index
 * @head: This is the address of pointer to first node
 * @index: This is the index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deletes_nodes_at_indexes(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int a = 0;

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
		if (a == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * frees_lists - This function frees all nodes of a list
 * @head_ptr: This is the address of pointer to head node
 *
 * Return: void
 */
void frees_lists(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
