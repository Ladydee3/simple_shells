#include "shell.h"

/**
 * is_chain - Function that test current char in buffer
 * @info: the struct
 * @buf: char buffer
 * @x: the address
 * Return: 1 if chain is delim, or 0 if otherwise
 */
int is_chain(info_t *info, char *buf, size_t *x)
{
	size_t a = *x;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';') /* found end of this command */
	{
		buf[a] = 0; /* replace semicolon with NULL */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*x = a;
	return (1);
}

/**
 * check_chain - Functiont hat checks if we should continue
 * chaining based on last status
 * @info: the struct
 * @buf: char buffer
 * @x: the address
 * @c: starting position
 * @len: length of buffer
 *
 * Return: Always 0
 */
void check_chain(info_t *info, char *buf, size_t *x, size_t c, size_t len)
{
	size_t k = *x;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[c] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[c] = 0;
			k = len;
		}
	}

	*x = k;
}

/**
 * replace_alias - Function that replaces an alias
 * in the tokenized string
 * @info: the struct
 * Return: 1 if replaced, or 0 if otherwise
 */
int replace_alias(info_t *info)
{
	int c;
	list_t *node;
	char *x;

	for (c = 0; c < 10; c++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		x = _strchr(node->str, '=');
		if (!x)
			return (0);
		x = _strdup(x + 1);
		if (!x)
			return (0);
		info->argv[0] = x;
	}
	return (1);
}

/**
 * replace_vars - Function that replaces vars in tokenized string
 * @info: the struct
 * Return: 1 if replaced, or 0 if otherwise
 */
int replace_vars(info_t *info)
{
	int x = 0;
	list_t *node;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			replace_string(&(info->argv[x]),
					_strdup(_convert_number(getpid(), 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]),
					_strdup(_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[x][1], '=');
		if (node)
		{
			replace_string(&(info->argv[x]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - Function that replaces a string
 * @old: old string
 * @new: new string
 * Return: 1 if replaced, or 0 if otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
