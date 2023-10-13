#include "main.h"
/**
* _strsdup - duplicates a string
* @s: the string to duplicate
* Return: pointer to the duplicated string
*/

char *_strsdup(const char *s)
{
	int len = 0;
	char *ret;

	if (s == NULL)
		return (NULL);
	while (*s++)
	len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--s;
	return (ret);
}

/**
* _puts - prints an input string
* @s: the string
* Return: Nothing
*/
void _puts(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}

/**
* _putchar - writes the character c to stdout
* @c: The character to print
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/

int _putchar(char c)
{
	static int i;
	static char buf[BUF_SIZE];

	if (c == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * *_strscpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 */

char *_strscpy(char *dest, char *src, int n)
{
	int i = 0, j;
	char *s = dest;

	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
			dest[j] = '\0', j++;
	}
	return (s);
}

/**
 **_strscat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */

char *_strscat(char *dest, char *src, int n)
{
	int i = 0, j = 0;
	char *s = dest;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
		dest[i] = src[j], i++, j++;
	if (j < n)
		dest[i] = '\0';
	return (s);
}
