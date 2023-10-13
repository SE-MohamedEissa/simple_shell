#include "main.h"

/**
* gets_environ - returns the string array
* @inf: Structure
* Return: Always 0
*/
char **gets_environ(inf_type *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = lst_tostrs(inf->env);
		inf->env_changed = 0;
	}
	return (inf->environ);
}

/**
* _unsetsenv - Remove
* @inf: Structure
* @var: the string env var property
*  Return: 1 on delete, 0
*/

int _unsetsenv(inf_type *inf, char *var)
{
	list_type *node = inf->env;
	size_t i = 0;
	char *m;

	if (!node || !var)
		return (0);
	while (node)
	{
		m = sta_with(node->str, var);
		if (m && *m == '=')
		{
			inf->env_changed = del_node_at_ndex(&(inf->env), i);
			i = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (inf->env_changed);
}

/**
* _setsenv - Initialize
* @inf: Structure
* @var: string
* @val: string
*  Return: Always 0
*/
int _setsenv(inf_type *inf, char *var, char *val)
{
	char *buf = NULL;
	list_type *node;
	char *p;

	if (!var || !val)
		return (0);
	buf = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, val);
	node = info->env;
	while (node)
	{
		p = sta_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(inf->env), buf, 0);
	free(buf);
	inf->env_changed = 1;
	return (0);
}
