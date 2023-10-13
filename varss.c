#include "main.h"

/**
* is_chain - test
* @inf: struct
* @bufe: buffer
* @po: address
* Return: 1 if chain delimeter, 0 otherwise
*/

int is_chain(inf_type *inf, char *bufe, size_t *po)
{
	size_t j = *po;

	if (bufe[j] == '|' && bufe[j + 1] == '|')
	{
		bufe[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (bufe[j] == '&' && bufe[j + 1] == '&')
	{
		bufe[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (bufe[j] == ';')
	{
		bufe[j] = 0;
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*po = j;
	return (1);
}

/**
* ch_chain - checks
* @inf: struct
* @bufe: buffer
* @po: address
* @i: input
* @len: length of buf
* Return: Void
*/
void ch_chain(inf_type *inf, char *bufe, size_t *po, size_t i, size_t len)
{
	size_t j = *po;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			bufe[i] = 0;
			j = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			bufe[i] = 0;
			j = len;
		}
	}
	*po = j;
}

/**
* repl_alias - replaces an aliases
* @inf: struct
* Return: 1 if replaced, 0 otherwise
*/

int repl_alias(inf_type *inf)
{
	int i;
	list_type *node;
	char *po;

	for (i = 0; i < 10; i++)
	{
		node = node_sta_with(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		po = _strnchr(node->str, '=');
		if (!po)
			return (0);
		po = _strsdup(po + 1);
		if (!po)
			return (0);
		inf->argv[0] = po;
	}
	return (1);
}

/**
* repl_var - replaces
* @inf: struct
* Return: 1 if replaced, 0 otherwise
*/
int repl_var(inf_type *inf)
{
	int i = 0;
	list_type *node;

	for (i = 0; inf->argv[i]; i++)
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;
		if (!_strcmp(inf->argv[i], "$?"))
		{
			repl_str(&(inf->argv[i]),
			_strsdup(conv_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[i], "$$"))
		{
			repl_str(&(inf->argv[i]),
			_strsdup(conv_number(getpid(), 10, 0)));
			continue;
		}
		node = node_sta_with(inf->env, &inf->argv[i][1], '=');
		if (node)
		{
			repl_str(&(inf->argv[i]),
			_strsdup(_strnchr(node->str, '=') + 1));
			continue;
		}
		repl_str(&inf->argv[i], _strsdup(""));
	}
	return (0);
}

/**
* repl_str - replaces string
* @o: address of old str
* @n: new str
* Return: 1 if replaced, 0 otherwise
*/

int repl_str(char **o, char *n)
{
	free(*o);

	*o = n;
	return (1);
}
