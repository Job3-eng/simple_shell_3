#include "shell.h"

/**
 * add_node - adding nodes
 * @head: node pointer address
 * @str: str node
 * @num: node indexing
 *
 * Return: size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_heads;

	if (!head)
		return (NULL);
	new_heads = malloc(sizeof(list_t));
	if (!new_heads)
		return (NULL);
	_memset((void *)new_heads, 0, sizeof(list_t));
	new_heads->num = num;
	if (str)
	{
		new_heads->str = _strdup(str);
		if (!new_heads->str)
		{
			free(new_heads);
			return (NULL);
		}
	}
	new_heads->next = *head;
	*head = new_heads;
	return (new_heads);
}

/**
 * add_node_end - adding nodes
 * @head:pointer  address
 * @str: str node
 * @num: node indexing
 *
 * Return: size
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_nodes, *nodes;

	if (!head)
		return (NULL);

	nodes = *head;
	new_nodes = malloc(sizeof(list_t));
	if (!new_nodes)
		return (NULL);
	_memset((void *)new_nodes, 0, sizeof(list_t));
	new_nodes->num = num;
	if (str)
	{
		new_nodes->str = _strdup(str);
		if (!new_nodes->str)
		{
			free(new_nodes);
			return (NULL);
		}
	}
	if (nodes)
	{
		while (nodes->next)
			nodes = nodes->next;
		nodes->next = new_nodes;
	}
	else
		*head = new_nodes;
	return (new_nodes);
}

/**
 * print_list_str - printing string
 * @h: pointer node
 *
 * Return: size
 */
size_t print_list_str(const list_t *h)
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
 * delete_node_at_index - deleting nodes
 * @head: node pointer address
 * @index: node index
 *
 * Return: 1 success, 0 otherwise.
 */
int delete_node_at_index(list_t **head, unsigned int index)
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
 * free_list - freeing nodes
 * @head_ptr: node pointer addresse
 *
 * Return: voiding
 */
void free_list(list_t **head_ptr)
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
