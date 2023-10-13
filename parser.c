#include "main.h"

/**
* is_cmd - determines
* @info: struct
* @path: path to the file
* Return: 1 if true, 0 otherwise
*/
int is_cmd(inf_type *info, char *path)
{
	struct stat s;

	(void)info;
	if (!path || stat(path, &s))
		return (0);
	if (s.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
* dup_ch - duplicates characters
* @pathstr: PATH string
* @start: input
* @stop: input
* Return: pointer to new buffer
*/
char *dup_ch(char *pathstr, int start, int stop)
{

	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)

	if (pathstr[i] != ':')
		buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
* fnd_path - finds this cmd in the PATH string
* @info: struct
* @pathstr: the PATH string
* @cmd: the cmd to find
* Return: full path of cmd if found or  NULL
*/

char *fnd_path(inf_type *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && sta_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
		return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_ch(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);

			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);

			if (!pathstr[i])
				break;
			curr_pos = i;

		}
		i++;
	}

	return (NULL);

}
