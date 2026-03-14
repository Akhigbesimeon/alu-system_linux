#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/reg.h>

/**
 * main - Traces a command and prints syscall numbers
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environment variables
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[], char *envp[])
{
    pid_t child;
    int status;
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
        /* CHILD: Start tracing and execute the command */
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execve(argv[1], argv + 1, envp);
        perror("execve");
        exit(1);
    }
    else
    {
        /* PARENT: Wait for child to stop at the first signal */
        wait(&status);
        /* Set option to distinguish syscalls from signals */
        ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);

        while (WIFSTOPPED(status))
        {
            /* Intercept entry into syscall */
            if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
                break;
            wait(&status);

            if (!WIFSTOPPED(status))
                break;

            /* Read register state to get syscall number */
            if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
                break;

            /* Print orig_rax (syscall number) */
            printf("%lu\n", (unsigned long)regs.orig_rax);

            /* Run until syscall exit to avoid double-printing */
            if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
                break;
            wait(&status);
        }
    }
    return (0);
}
