#include "main.h"

/**
 * _eputs - prints an input string
 * @s: the string to be printed
 * Return: Nothing
 */

void _eputs(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_erputchar(s[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _eputfd - writes the character c to given fd
 * @v: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _eputfd(char v, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (v == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (v != BUF_FLUSH)
		buf[i++] = v;

	return (1);
}

/**
 * _eputsfd - prints an input string
 * @s: the string to be printed
 * @f: the filedescriptor to write to
 * Return: the number of chars put
 */

int _eputsfd(char *s, int f)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += _eputfd(*s++, fd);
	}

	return (i);
}
