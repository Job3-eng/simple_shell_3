#include "shell.h"

/**
 * list_len - determining length
 * @h: nodes pointer
 *
 * Return: size
 */
size_t list_len(const list_t *h)
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
 * list_to_strings - returning strings
 * @head: nodes pointer
 *
 * Return: strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t m = list_len(head), n;
	char **strs;
	char *str;

	if (!head || !m)
		return (NULL);
	strs = malloc(sizeof(char *) * (m + 1));
	if (!strs)
		return (NULL);
	for (m = 0; node; node = node->next, m++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (n = 0; n < m; n++)
				free(strs[n]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[m] = str;
	}
	strs[m] = NULL;
	return (strs);
}


/**
 * print_list - printing elements
 * @h: nodes pointer
 *
 * Return: size
 */
size_t print_list(const list_t *h)
{
	size_t m = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		m++;
	}
	return (m);
}

/**
 * node_starts_with - returning nodes
 * @node: pointer
 * @prefix: str
 * @c: charfor  match
 *
 * Return: nodes , nulls
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *b = NULL;

	while (node)
	{
		b = starts_with(node->str, prefix);
		if (b && ((c == -1) || (*b == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - getting node of  index
 * @head: pointer
 * @node: nodes pointer
 *
 * Return: nodes indes or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
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

