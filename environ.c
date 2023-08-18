#include "shell.h"

/**
 * _myenv - Function that prints the current env
 * @str: the structure
 * Return: 0 on success
 */
int _myenv(info_t *str)
{
	print_list(str->env);
	return (0);
}

/**
 * _getenv - Function that gets a value of env variable
 * @str: the structure
 * @var: the variable name
 * Return: The results
 */
char *_getenv(info_t *str, const char *var)
{
	list_t *node = str->env;
	char *x;

	while (node)
	{
		x = starts_with(node->str, var);
		if (x && *x)
			return (x);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Function that initialize new env or modify existing one
 * @str: the structure
 * Return: 0 on success
 */
int _mysetenv(info_t *str)
{
	if (str->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(str, str->argv[1], str->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Function that removes an environmental variable
 * @str: the structure
 * Return: 0 on success
 */
int _myunsetenv(info_t *str, char *a)
{
	int x;

	if (str->argc == 1)
	{
		_eputs("Too few arguements\n");
		return (1);
	}
	for (x = 1; x <= str->argc; x++)
		_unsetenv(str, str->argv[x]);
	return (0);
}

/**
 * populate_env_list - Function that populates env linked list
 * @str: the structure
 * Return: 0 on success
 */
int populate_env_list(info_t *str)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		add_node_end(&node, environ[x], 0);
	str->env = node;
	return (0);
}
