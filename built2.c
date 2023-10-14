#include "main.h"

/**
 * _minehistory - displays the history list
 * @info: struct
 *  Return: 0 always
 */
int _minehistory(inf_type *info)
{
	pr_lst(info->history);
	return (0);
}
/**
 * unsets_alias - sets alias to string
 * @info: structure
 * @str:  string alias
 * Return: success 0,  error 1.
 */
int unsets_alias(inf_type *info, char *str)
{
	char *q, s;
	int ret;

	q = _strnchr(str, '=');
	if (!q)
		return (1);
	s = *q;
	*q = 0;
	ret = del_node_at_ndex(&(info->alias),
		get_node_ndex(info->alias, node_sta_with(info->alias, str, -1)));
	*q = s;
	return (ret);
}
/**
 * sets_alias - sets alias to string
 * @info: structure
 * @s: string alias
 * Return: on success 0, on error 1
 */
int sets_alias(inf_type *info, char *s)
{
	char *q;

	q = _strnchr(s, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unsets_alias(info, s));
	unsets_alias(info, s);
	return (add_node_end(&(info->alias), s, 0) == NULL);
}

/**
 * pr_alias - prints an alias
 * @node: alias node
 * Return: on success 0, 1 on error
 */

int pr_alias(list_type *node)
{
	char *q = NULL, *b = NULL;

	if (node)
	{
		q = _strnchr(node->str, '=');
		for (b = node->str; b <= q; b++)
		_putchar(*b);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _minealias - man alias
 * @info: structure
 *  Return: Always 0
 */
int _minealias(inf_type *info)
{
	int i = 0;
	char *q = NULL;
	list_type *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			pr_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		q = _strnchr(info->argv[i], '=');
		if (q)
			sets_alias(info, info->argv[i]);
		else
			pr_alias(node_sta_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
