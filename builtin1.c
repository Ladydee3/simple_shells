#include "shell.h"

/**
 * _myhistory - Function that displays the history list.
 * @str: the structure
 * Return: Nothing
 */
int _myhistory(info_t *str)
{
	print_list(str->history);
	return (0);
}

/**
 * unset_alias - Function that sets alias to string.
 * @str: the structure
 * @s: the string
 * Return: 0 on success,1 on error
 */
int unset_alias(info_t *str, char *s)
{
	char *x, y;
	int ret;

	x = _strchr(s, '=');
	if (!x)
		return (1);
	y = *x;
	*x = 0;
	ret = delete_node_at_index(&(str->alias),
			get_node_index(str->alias, node_starts_with(str->alias, s, -1)));
	*x = y;
	return (ret);
}

/**
 * set_alias - Function that sets alias to a string.
 * @str: the structure
 * @s: the string
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *str, char *s)
{
	char *x;

	x = _strchr(s, '=');
	if (!x)
		return (1);
	if (!*++x)
		return (unset_alias(str, s));

	unset_alias(str, s);
	return (add_node_end(&(str->alias), s, 0) == NULL);
}

/**
 * print_alias - Function that prints an alias to string.
 * @node: the node
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *x = NULL, *c = NULL;

	if (node)
	{
		x = _strchr(node->str, '=');
		for (c = node->str; c <= x; c++)
			_putchar(*c);
		_putchar('\n');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myalias - Function that mimics the alias builtin.
 * @str: the structure
 * Return: Nothing
 */
int _myalias(info_t *str)
{
	int b = 0;
	char *x = NULL;
	list_t *node = NULL;

	if (str->argc == 1)
	{
		node = str->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (b = 1; str->argv[b]; b++)
	{
		x = _strchr(str->argv[b], '=');
		if (x)
			set_alias(str, str->argv[b]);
		else
			print_alias(node_starts_with(str->alias, str->argv[b], '='));
	}

	return (0);
}
