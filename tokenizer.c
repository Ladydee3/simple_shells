#include "shell.h"

/**
 * **strtow - Function that splits a string into words
 * @str: the string
 * @delim: the delimeter
 * Return: 1 if success, or NULL if otherwise
 */
char **_strtow(char *str, char delim)
{
	int a, b, x, y, numwords = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], delim) && (is_delim(str[a + 1], delim) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	c = malloc((1 + numwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (is_delim(str[a], delim))
			a++;
		x = 0;
		while (!is_delim(str[a + x], delim) && str[a + x])
			x++;
		c[b] = malloc((x + 1) * sizeof(char));
		if (!c[b])
		{
			for (x = 0; x < b; x++)
				free(c[x]);
			free(c);
			return (NULL);
		}
		for (y = 0; y < x; y++)
			c[b][y] = str[a++];
		c[b][y] = 0;
	}
	c[b] = NULL;
	return (c);
}

/**
 * **strtow2 - Function that splits a string into words
 * @str: the string
 * @delim: the delimeter
 * Return: a pointer, or NULL if otherwise
 */
char **strtow2(char *str, char *delim)
{
	int a, b, x, y, numwords = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != delim && str[a + 1] == delim) || (str[a] != delim && !str[a + 1]) || str[a + 1] == delim)
			numwords++;
	if (numwords == 0)
		return (NULL);
	c = malloc((1 + numwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (str[a] == delim && str[a] != delim)
			a++;
		x = 0;
		while (str[a + x] != delim && str[a + x] && str[a + x] != delim)
			x++;
		c[b] = malloc((x + 1) * sizeof(char));
		if (!c[b])
		{
			for (x = 0; x < b; x++)
				free(c[x]);
			free(c);
			return (NULL);
		}
		for (y = 0; y < x; y++)
			c[b][y] = str[a++];
		c[b][y] = 0;
	}
	c[b] = NULL;
	return (c);
}
