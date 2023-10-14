#include "main.h"


/**
* input_buf - buffers chained commands
* @info: parameter struct
* @buf: address of buffer
* @len: address of len var
* Return: bytes read
*/

ssize_t input_buf(inf_type *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{

		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

		#if GETLINE_USE
			r = _getsline(buf, &len_p, stdin);
		#else
			r = _getsline(info, buf, &len_p);

		#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			rmov_comments(*buf);
			buld_his_lst(info, *buf, info->histcount++);
			if (_strnchr(*buf, ';'))
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
* gets_input - gets a line
* @info: parameter struct
* Return: bytes read
*/
ssize_t gets_input(inf_type *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;
		ch_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (r);
}

/**
* red_buf - reads a buffer
* @info: parameter struct
* @buf: buffer
* @i: size
*
* Return: r
*/
ssize_t red_buf(inf_type *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
* _getsline - gets line
* @info: parameter struct
* @ptr: address
* @length: size
* Return: s
*/
int _getsline(inf_type *info, char **ptr, size_t *length)
{
	static char buf[BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = red_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strnchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		_strscat(new_p, buf + i, k - i);
	else
		_strscpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
* sigintHandler - blocks ctrl-C
* @sig_num: the signal number
* Return: void
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
