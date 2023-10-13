#include "main.h"

/**
* cls_inf - initializes inf_type struct
* @info: struct address
*/

void cls_inf(inf_type *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
* sets_inf - initializes inf_type struct
* @info: struct address
* @av: argument vector
*/

void sets_inf(inf_type *info, char **av)
{
	int i = 0;

	info->finame = av[0];
	if (info->arg)
	{
		info->argv = strstow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strsdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		repl_alias(info);
		repl_var(info);
	}
}

/**
* fre_inf - frees info_type struct fields
* @info: struct address
* @all: true if freeing all fields
*/

void fre_inf(inf_type *info, int all)
{
	ffre(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			fre_lst(&(info->env));

		if (info->history)
			fre_lst(&(info->history));
		if (info->alias)
			fre_lst(&(info->alias));
		ffre(info->environ);
		info->environ = NULL;
		bfre((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
/**
 * _getsenv - gets the value of an environ variable
 * @info:  this struct containing potential arguments.
 * @name: env var name
 * Return: the value
 */
char *_getsenv(inf_type *info, const char *name)
{
	list_type *node = info->env;
	char *y;

	while (node)
	{
		y = sta_with(node->str, name);
		if (y && *y)
			return (y);
		node = node->next;
	}
	return (NULL);
}

