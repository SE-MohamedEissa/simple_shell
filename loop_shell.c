#include "main.h"

/**
* hash - main shell loop
* @info: struct
* @av: the argument vector from main()
* Return: 0 on success, 1 on error, or error code
*/

int hash(inf_type *info, char **av)
{
	ssize_t u = 0;
	int builtin_rt = 0;

	while (u != -1 && builtin_rt != -2)
	{
		cls_inf(info);
		if (interactives(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		u = gets_input(info);
		if (u != -1)
		{
			sets_inf(info, av);
			builtin_rt = f_builtin(info);
			if (builtin_rt == -1)
				fnd_cmd(info);
		}
		else if (interactives(info))
			_putchar('\n');
		fre_inf(info, 0);
	}
	write_his(info);
	fre_inf(info, 1);
	if (!interactives(info) && info->status)
		exit(info->status);
	if (builtin_rt == -2)
	{
		if (info->err_num == -1)
		{
			exit(info->status);
			exit(info->err_num);
		}
	}
	return (builtin_rt);
}

/**
* f_builtin - finds a builtin command
* @info: struct
* Return: -1 if builtin not found,
* 0 if builtin executed successfully,
* 1 if builtin found but not successful,
* 2 if builtin signals exit()
*/

int f_builtin(inf_type *info)
{
	int i, built_in_rt = -1;

	builtin_type builtintbl[] = {
		{"exit", _mineexit},
		{"env", _mineenv},
		{"help", _minehelp},
		{"history", _minehistory},
		{"setenv", _minesetenv},
		{"unsetenv", _mineunsetenv},
		{"cd", _minecd},
		{"alias", _minealias},
		{NULL, NULL}
	};
	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_rt = builtintbl[i].func(info);
			break;
		}
	return (built_in_rt);
}

/**
* fnd_cmd - finds a command in PATH
* @info: struct
*
* Return: void
*/
void fnd_cmd(inf_type *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
	{
		if (!is_delimet(info->arg[i], " \t\n"))
			k++;
		if (!k)
			return;
	}
	path = fnd_path(info, _getsenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		frk_cmd(info);
	}
	else
	{
		if ((interactives(info) || _getsenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))

			frk_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			pr_error(info, "not found\n");
		}
	}
}

/**
* frk_cmd - forks a an exec thread to run cmd
* @info: struct
* Return: void
*/
void frk_cmd(inf_type *info)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		pr_error(info, "Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, gets_environ(info)) == -1)
		{
			fre_inf(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				pr_error(info, "Permission denied\n");
		}
	}
}
