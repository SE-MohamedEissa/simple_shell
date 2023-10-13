#include "main.h"


/**
 * _mineenv -  this  prints the current environ
 * @info: struct
 * Return: Always 0
 */

int _mineenv(inf_type *info)
{
	pr_lst_str(info->env);
	return (0);
}

/**
 * _minesetenv - Initialize a new envir
 * @info: struct
 *  Return: Always 0
 */
int _minesetenv(inf_type *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setsenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _mineunsetenv - remove envir
 * @info: struct
 * Return: Always 0
 */
int _mineunsetenv(inf_type *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetsenv(info, info->argv[i]);
	return (0);
}

/**
 * pop_env_list - populates env
 * @info: structure
 * Return: Always 0
 */
int pop_env_list(inf_type *info)
{
	list_type *ndee = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&ndee, environ[i], 0);
	info->env = ndee;
	return (0);
}
