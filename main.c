#include "shell.h"

/**
 * main - The entry point
 * @argc: the arg count
 * @argv: the arg vector
 * Return: Always 0 (success), or 1 on error
 */
int main(int argc, char *argv)
{
	info_t info[] = {INFO_INIT};
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=c" (fd)
			: "c" (fd));

	if (argc == 2)
	{
		fd = open(char *argv[], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				EXIT(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	hsh(info, argv);
	read_history(info);
	return (EXIT_SUCCESS);
}
