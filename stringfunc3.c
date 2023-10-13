#include "main.h"

/**
 **_strnchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */

char *_strnchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
/**
* **strstow - splits a string into words.
* @str: the input string
* @d: the delimeter string
* Return: a pointer to an array of strings, or NULL on failure
*/

char **strstow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimet(str[i], d) && (is_delimet(str[i + 1], d) || !str[i + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delimet(str[i], d))
			i++;
		k = 0;
		while (!is_delimet(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
* **strstowar - splits a string into words
* @str: the input string
* @d: the delimeter
* Return: a pointer to an array of strings, or NULL on failure
*/
char **strstowar(char *str, char d)
{
	int i, j, k, m, len = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != d && str[i + 1] == d) ||
			(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			len++;
		if (len == 0)
			return (NULL);
		s = malloc((1 + len) * sizeof(char *));
		if (!s)
			return (NULL);
	}
		for (i = 0, j = 0; j < len; j++)
		{
			while (str[i] == d && str[i] != d)
				i++;
			k = 0;
			while (str[i + k] != d && str[i + k] && str[i + k] != d)
				k++;
			s[j] = malloc((k + 1) * sizeof(char));
			if (!s[j])
			{
				for (k = 0; k < j; k++)
					free(s[k]);
				free(s);
				return (NULL);
			}
			for (m = 0; m < k; m++)
				s[j][m] = str[i++];
			s[j][m] = 0;
		}
		s[j] = NULL;
		return (s);
}
