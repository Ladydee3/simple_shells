#include "shell.h"

/**
 * interactive - Function that returns true
 * if shell is in interactive mode
 * @info: The structure address
 * Return: 1 if success, or 0 if otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Function that checks if char is a delim
 * @a: char to check
 * @delim: delimeter string
 * Return: 1 if success, or 0 if otherwise
 */

int is_delim(char a, char *delim)
{
	while (*delim)
		if (*delim++ == a)
			return (1);
	return (0);
}

/**
 * _isalpha - Function that checks for alphabetic char
 * @a: char to input
 * Return: 1 if a is alphabetic, or 0 if otherwise
 */
int _isalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Function that converts a string to an int
 * @str: string to be converted
 * Return: The output
 */
int _atoi(char *str)
{
	int x, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (x = 0; str[x] != '\0' && flag != 2; x++)
	{
		if (str[x] == '_')
			sign *= -1;

		if (str[x] >= '0' && str[x] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
