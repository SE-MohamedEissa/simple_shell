#include "main.h"

/**
* get_his_fl - gets the history file
* @inf: parameter struct
* Return: v
*/

char *get_his_fl(inf_type *inf)
{
	char *bufe, *dir;

	dir = _getsenv(inf, "HOME=");
	if (!dir)
		return (NULL);
	bufe = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTORY_FILE) + 2));
	if (!bufe)
		return (NULL);
	bufe[0] = 0;
	_strcpy(bufe, dir);
	_strcat(bufe, "/");
	_strcat(bufe, HISTORY_FILE);
	return (bufe);
}

/**
* write_his - creates a file, or appends to an existing file
* @inf: the parameter struct
* Return: 1 on success, else -1
*/
int write_his(inf_type *inf)
{
	ssize_t fid;
	char *fin = get_his_fl(inf);
	list_type *node = NULL;

	if (!fin)
		return (-1);
	fid = open(fin, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fin);
	if (fid == -1)
		return (-1);
	for (node = inf->history; node; node = node->next)
	{
		_eputsfd(node->str, fid);
		_eputfd('\n', fid);
	}
	_eputfd(BUF_FLUSH, fid);
	close(fid);
	return (1);
}

/**
* red_his - reads history from file
* @inf: the parameter struct
* Return: histcount on success, 0 otherwise
*/

int red_his(inf_type *inf)
{
	int i, last = 0, lin_cnt = 0;
	ssize_t fid, rdlen, fsize = 0;
	struct stat st;
	char *bufe = NULL, *fin = get_his_fl(inf);

	if (!fin)
		return (0);
	fid = open(fin, O_RDONLY);
	free(fin);
	if (fid == -1)
		return (0);
	if (!fstat(fid, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	bufe = malloc(sizeof(char) * (fsize + 1));
	if (!bufe)
		return (0);
	rdlen = read(fid, bufe, fsize);
	bufe[fsize] = 0;
	if (rdlen <= 0)
		return (free(bufe), 0);
	close(fid);
	for (i = 0; i < fsize; i++)
		if (bufe[i] == '\n')
		{
			bufe[i] = 0;
			buld_his_lst(inf, bufe + last, lin_cnt++);
			last = i + 1;
		}
	if (last != i)
		buld_his_lst(inf, bufe + last, lin_cnt++);
	free(bufe);
	inf->histcount = lin_cnt;
	while (inf->histcount-- >= HISTORY_MAX)
		del_node_at_ndex(&(inf->history), 0);
	renum_history(inf);
	return (inf->histcount);
}

/**
* buld_his_lst - adds entry to a history linked list
* @inf: Structure containing potential arguments. Used to maintain
* @bufe: buffer
* @lin_cnt: the history linecount, histcount
* Return: Always 0
*/

int buld_his_lst(inf_type *inf, char *bufe, int lin_cnt)
{
	list_type *node = NULL;

	if (inf->history)
		node = inf->history;
	add_node_end(&node, bufe, lin_cnt);
	if (!inf->history)
		inf->history = node;
	return (0);
}

/**
* renum_history - renumbers the history linked list after changes
* @inf: Structure containing potential arguments. Used to maintain
* Return: the new histcount
*/

int renum_history(inf_type *inf)
{
	list_type *node = inf->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (inf->histcount = i);
}
