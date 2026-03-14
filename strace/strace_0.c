#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

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
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        /* Stop the child so the parent can set options */
        kill(getpid(), SIGSTOP);
        execve(argv[1], argv + 1, envp);
        perror("execve");
        exit(1);
    }
    else
    {
        waitpid(child, &status, 0);
        /* Set option to distinguish syscall stops from signals */
        ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);

        while (1)
        {
            /* 1. Stop at Syscall Entry */
            if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
                break;
            waitpid(child, &status, 0);
            if (WIFEXITED(status) || WIFSIGNALED(status))
                break;

            /* 2. Read and print syscall number at Entry */
            if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
                break;
            
            /* In x86_64, orig_rax holds the syscall number */
            printf("%lu\n", (unsigned long)regs.orig_rax);
            fflush(stdout);

            /* 3. Stop at Syscall Exit (and ignore it) */
            if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
                break;
            waitpid(child, &status, 0);
            if (WIFEXITED(status) || WIFSIGNALED(status))
                break;
        }
    }
    return (0);
}
