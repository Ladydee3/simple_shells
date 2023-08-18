#include "shell.h"
#include <stddef.h>

/**
 * _strcpy - Function that copies a string
 * @dest: destination
 * @src: source
 * Return: A pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * _strdup - Function that duplicates a string
 * @s: A string
 * Return: A pointer to dup string
 */
char *_strdup(const char *s)
{
	int len = 0;
	char *x;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	x = malloc(sizeof(char) * (len + 1));

	if (!x)
		return (NULL);
	for (len++; len--;)
		x[len] = *--s;
	return (x);
}

/**
 * _puts - Function that prints a string
 * @s: A string
 * Return: Nothing
 */
void _puts(char *s)
{
	int x = 0;

	if (!s)
		return;
	while (s[x] != '\0')
	{
		_putchar(s[x]);
		x++;
	}
}

/**
 * _putchar - Function that writes char x to stdout
 * @x: the char
 * Return: On success 1
 * On errno, -1 is returned, and errno is set appropriately
 */
int _putchar(char x)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (x != BUF_FLUSH)
		buf[a++] = x;
	return (1);
}
