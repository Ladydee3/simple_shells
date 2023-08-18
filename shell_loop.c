#include "shell.h"

/**
 * hsh - The main shell loop
 * @str: the structure
 * @av: the arguement
 * Return: Always 0 (success), 1 on error code
 */
int hsh(info_t *str, char *av)
{
	ssize_t x = 0;
	int builtin_ret = 0;

	while (x != -1 && builtin_ret != -2)
	{
		clear_info(str);
		if (interactive(str))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		x = get_input(str);
		if (x != -1)
		{
			set_info(str, av);
			builtin_ret = find_builtin(str);
			if (builtin_ret == -1)
				find_cmd(str);
		}
		else if (interactive(str))
			_putchar('\n');
		free_info(str, 0);
	}
	write_history(str);
	free_info(str, 1);
	if (!interactive(str) && str->status)
		exit(str->status);
	if (builtin_ret == -2)
	{
		if (str->err_num == -1)
			exit(str->status);
		exit(str->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - Function that finds builtin command
 * @str: the structure
 * Return: -1 if not found
 * 0 if found successfully
 * 1 if found but not successful
 * 2 if signal exit()
 */
int find_builtin(info_t *str)
{
	int x, builtin_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(str->argv[0], builtintbl[x].type) == 0)
		{
			str->line_count++;
			builtin_ret = builtintbl[x].func(str);
			break;
		}
	return (builtin_ret);
}

/**
 * find_cmd - Function that fins a comman in PATH
 * @str: the structure
 * Return: Nothing
 */
void find_cmd(info_t *str)
{
	char *path = NULL;
	int x, y;

	str->path = str->argv[0];
	if (str->linecount_flag == 1)
	{
		str->line_count++;
		str->linecount_flag = 0;
	}
	for (x = 0, y = 0; str->arg[x]; x++)
		if (!is_delim(str->arg[x], " \t\n"))
			y++;

	if (!y)
		return;

	path = find_path(str, _getenv(str, "PATH="), str->argv[0]);
	if (path)
	{
		str->path = path;
		fork_cmd(str);
	}
	else
	{
		if ((interactive(str) || _getenv(str, "PATH=")
					|| str->argv[0][0] == '/') && is_cmd(str, str->argv[0]))
			fork_cmd(str);
		else if (*(str->arg) != '\n')
		{
			str->status = 127;
			print_error(str, "not found\n");
		}
	}
}

/**
 * fork_cmd - Forks an exec thread to run cmd
 * @str: the structure
 * Return: Nothing
 */
void fork_cmd(info_t *str)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("ERROR:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(str->path, str->argv, get_environ(str)) == -1)
		{
			free_info(str, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(str->status));
		{
			str->status = WEXITSTATUS(str->status);
			if (str->status == 126)
				print_error(str, "Permission denied\n");
		}
	}
}
