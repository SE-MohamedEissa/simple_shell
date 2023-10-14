#include "main.h"


/**
* add_node - adds a node to the start of the list
* @head: address of pointer to head node
* @s: str field of node
* @n: node index used by history
* Return: size of list
*/

list_type *add_node(list_type **head, const char *s, int n)
{
	list_type *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_type));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_type));
	new_head->num = n;
	if (s)
	{
		new_head->str = _strsdup(s);
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
* add_node_end - adds a node to the end of the list
* @head: address of pointer to head node
* @s: str field of node
* @n: node index used by history
* Return: size of list
*/

list_type *add_node_end(list_type **head, const char *s, int n)
{
	list_type *new_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(list_type));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_type));
	new_node->num = n;
	if (s)
	{
		new_node->str = _strsdup(s);
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
* pr_lst_str - prints only the str element of a list_t linked list
* @hd: pointer to first node
* Return: size of list
*/
size_t pr_lst_str(const list_type *hd)
{
	size_t i = 0;

	while (hd)
	{
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->next;
		i++;
	}
	return (i);
}

/**
* del_node_at_ndex - deletes node at given index
* @hd: address of pointer to first node
* @indx: index of node to delete
*
* Return: 1 on success, 0 on failure
*/

int del_node_at_ndex(list_type **hd, unsigned int indx)
{
	list_type *node, *prev_node;
	unsigned int i = 0;

	if (!hd || !*hd)
		return (0);
	if (!indx)
	{
		node = *hd;
		*hd = (*hd)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *hd;
	while (node)
	{
		if (i == indx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
* fre_lst - frees all nodes of a lis
* @hd_ptr: address of pointer to head node
*
* Return: void
*/
void fre_lst(list_type **hd_ptr)
{
	list_type *node, *next_node, *hd;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd = *hd_ptr;
	node = hd;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*hd_ptr = NULL;
}
