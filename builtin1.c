#include "shell.h"

/**
 * _myhistory - displayng history list from 0
 * @info: Structure with the args.
 *  Return: 0 success.
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - seting alias
 * @info: parameter structure
 * @str: string
 *
 * Return:  0 success 1  errors
 */
int unset_alias(info_t *info, char *str)
{
	char *b, d;
	int ret;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	d = *b;
	*b = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*b = d;
	return (ret);
}

/**
 * set_alias - setting alias
 * @info: parameter structure
 * @str: string
 *
 * Return:  0 success, 1  error
 */
int set_alias(info_t *info, char *str)
{
	char *b;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - printing string
 * @node: node aliasing
 *
 * Return: 0  success 1  errors
 */
int print_alias(list_t *node)
{
	char *b = NULL, *a = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		for (a = node->str; a <= b; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimicing builtin
 * @info: Structure with the args
 *  Return: 0 success
 */
int _myalias(info_t *info)
{
	int a = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		b = _strchr(info->argv[a], '=');
		if (b)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}

	return (0);
}
