#ifndef SYSCALLS_H
#define SYSCALLS_H

/**
 * struct syscall_s - Structure for syscall information
 * @name: The name of the syscall
 * @nr: The syscall number
 */
typedef struct syscall_s
{
    unsigned long nr;
    const char *name;
} syscall_t;

/* This is a truncated version of the x86_64 syscall table */
/* You can expand this as you progress through the tasks */
static const syscall_t syscalls_64[] = {
    {0, "read"},
    {1, "write"},
    {2, "open"},
    {3, "close"},
    {4, "stat"},
    {5, "fstat"},
    {9, "mmap"},
    {11, "munmap"},
    {12, "brk"},
    {21, "access"},
    {59, "execve"},
    {231, "exit_group"},
    /* ... add more as needed ... */
    {0, NULL}
};

#endif /* SYSCALLS_H */
