#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * main - Traces a command and prints syscall names using syscalls.h
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environment variables
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[], char *envp[])
{
	pid_t child;
	int status, is_entry = 1;
	struct user_regs_struct regs;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
		return (1);
	}

	child = fork();
	if (child == -1)
		return (1);

	if (child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		kill(getpid(), SIGSTOP);
		execve(argv[1], argv + 1, envp);
		perror("execve");
		exit(1);
	}
	else
	{
		waitpid(child, &status, 0);
		ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);

		while (1)
		{
			if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
				break;
			waitpid(child, &status, 0);
			if (WIFEXITED(status) || WIFSIGNALED(status))
				break;

			if (is_entry)
			{
				ptrace(PTRACE_GETREGS, child, NULL, &regs);
				
				/* Print the name using your syscalls_64_g array */
				printf("%s\n", syscalls_64_g[regs.orig_rax].name);
				fflush(stdout);
				is_entry = 0;
			}
			else
			{
				is_entry = 1;
			}
		}
	}
	return (0);
}
