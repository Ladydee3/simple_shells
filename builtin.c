#include "shell.h"

/**
 * _myexit - Function that exits the shell
 * @str: the structure
 * Return: The exit status
 */
int _myexit(info_t *str)
{
	int exits;

	if (str->argv[1]) /*If there is an exit arguement */
	{
		exits = erratoi(str->argv[1]);
		if (exits == -1)
		{
			str->status = 2;
			print_error(str, "Illegal number: ");
			_eputs(str->argv[1]);
			_eputchar('\n');
			return (1);
		}
		str->err_num = erratoi(str->argv[1]);
		return (-2);
	}
	str->err_num = -1;
	return (-2);
}

/**
 * _mycd - Function that changes the current directory
 * of the process
 * @str: the structure
 * Return: Nothing
 */
int _mycd(info_t *str)
{
	char *x, *d, buf[1024];
	int chdir_ret;

	x = getcwd(buf, 1024);
	if (!x)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!str->argv[1])
	{
		d = _getenv(str, "HOME=");
		if (!d)
			chdir_ret = /* TODO: what should this be? */
				chdir((d = _getenv(str, "PWD=")) ? d : "/");
		else
			chdir_ret = chdir(d);
	}
	else if (_strcmp(str->argv[1], "-") == 0)
	{
		if (!_getenv(str, "OLDPWD="))
		{
			_puts(x);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(str, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((d = _getenv(str, "OLDPWD=")) ? d : "/");
	}
	else
		chdir_ret = chdir(str->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(str, "can't cd to ");
		_eputs(str->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(str, "OLDPWD", _getenv(str, "PWD="));
		_setenv(str, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * _myhelp - Function that changes the current directory of the process
 * @str: the structure
 * Return: Nothing
 */
int _myhelp(info_t *str)
{
	char **arg_array;

	arg_array = str->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
