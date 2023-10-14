#include "main.h"
/**
* _mineexit - exits the shell
* @info: Structure
* Return: as code
*/
int _mineexit(inf_type *info)
{
	int exitch;

	if (info->argv[1])
	{
		exitch = _erratoi(info->argv[1]);
		if (exitch == -1)
		{
			info->status = 2;
			pr_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
* _minecd - changes directory
* @info: the struct
* Return: Always 0
*/
int _minecd(inf_type *info)
{
	char *s, *dir, buf[1024];
	int chdir_rt;

	s = getcwd(buf, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getsenv(info, "HOME=");
		if (!dir)
			chdir_rt =
				chdir((dir = _getsenv(info, "PWD=")) ? dir : "/");
		else
			chdir_rt = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getsenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getsenv(info, "OLDPWD=")), _putchar('\n');
		chdir_rt = chdir((dir = _getsenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_rt = chdir(info->argv[1]);
	if (chdir_rt == -1)
	{
		pr_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setsenv(info, "OLDPWD", _getsenv(info, "PWD="));
		_setsenv(info, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
* _minehelp - changes  directory
* @info: Structure
* Return: Always 0
*/
int _minehelp(inf_type *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");

	if (0)
		_puts(*arg_array);
	return (0);
}
