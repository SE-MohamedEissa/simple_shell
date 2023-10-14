#include "main.h"

/**
* lst_len - determines length of linked list
* @hd: pointer to first node
*
* Return: size of list
*/

size_t lst_len(const list_type *hd)
{
	size_t i = 0;

	while (hd)
	{
		hd = hd->next;
		i++;
	}
	return (i);
}

/**
* lst_tostrs - returns an array of strings of the list->str
* @hd: pointer to first node
*
* Return: array of strings
*/

char **lst_tostrs(list_type *hd)
{
	list_type *node = hd;
	size_t i = lst_len(hd), j;
	char **str1;
	char *str;

	if (!hd || !i)
		return (NULL);
	str1 = malloc(sizeof(char *) * (i + 1));
	if (!str1)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(str1[j]);
			free(str1);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		str1[i] = str;
	}
	str1[i] = NULL;
	return (str1);
}

/**
* pr_lst - prints all elements of a list_t linked list
* @hd: pointer to first node
*
* Return: size of list
*/

size_t pr_lst(const list_type *hd)
{
	size_t i = 0;

	while (hd)
	{
		_puts(conv_number(hd->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->next;
		i++;
	}
	return (i);
}

/**
* node_sta_with - returns node whose string starts with prefix
* @node: pointer to list head
* @pref: string to match
* @ch: the next character after prefix to match
*
* Return: match node or null
*/
list_type *node_sta_with(list_type *node, char *pref, char ch)
{
	char *po = NULL;

	while (node)
	{
		po = sta_with(node->str, pref);
		if (po && ((ch == -1) || (*po == ch)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
* get_node_ndex - gets the index of a node
* @hd: pointer to list head
* @node: pointer to the node
*
* Return: index of node or -1
*/

ssize_t get_node_ndex(list_type *hd, list_type *node)
{
	size_t i = 0;

	while (hd)
	{
		if (hd == node)
			return (i);
		hd = hd->next;
		i++;
	}
	return (-1);
}
