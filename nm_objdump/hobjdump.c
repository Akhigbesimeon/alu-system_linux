#include "hobjdump.h"

/**
 * main - Reproduces the objdump command using execve
 * @argc: The count of command-line arguments
 * @argv: The array of command-line arguments
 * @env: The environment variables array
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int argc, char **argv, char **env)
{
	char *av[] = {"/usr/bin/objdump", "-s", "-f", "", NULL};

	(void)argc;

	av[3] = argv[1];

	if (execve("/usr/bin/objdump", av, env) == -1)
	{
		perror("execv");
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
