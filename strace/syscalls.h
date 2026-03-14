#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>


/* Normally, MAX_PARAMS is always 6 */
#define MAX_PARAMS	6

#define IS_UINT(x) (x == UINT32_T || x == UNSIGNED_INT || x == GID_T ||\
	x == ID_T || x == MODE_T || x == SIZE_T || x == SOCKLEN_T || x == U64 ||\
	x == UID_T || x == UNSIGNED_LONG)
#define IS_LONG(x) (x == LONG || x == PID_T || x == SSIZE_T || x == CLOCK_T ||\
	x == TIME_T)

#define IS_INT(x) (x == CLOCKID_T || x == KEY_T || x == MQD_T ||\
	x == IDTYPE_T || x == INT || x == KEY_SERIAL_T ||\
	x == ENUM___PTRACE_REQUEST || x == PID_T)

#define IS_POINTER(x) (x == AIO_CONTEXT_T_P || x == CHAR_P ||\
	x == CPU_SET_T_P || x == FD_SET_P || x == GID_T_P || x == INT_P ||\
	x == LOFF_T_P || x == LONG_P || x == OFF_T_P || x == SIGINFO_T_P ||\
	x == SIGSET_T_P || x == SIZE_T_P || x == SOCKLEN_T_P || x == STACK_T_P ||\
	x == STRUCT_EPOLL_EVENT_P || x == STRUCT_GETCPU_CACHE_P ||\
	x == STRUCT_IOCB_P || x == STRUCT_IOVEC_P || x == STRUCT_IO_EVENT_P ||\
	x == STRUCT_ITIMERSPEC_P || x == STRUCT_ITIMERVAL_P ||\
	x == STRUCT_KERNEL_SYM_P || x == STRUCT_KEXEC_SEGMENT_P ||\
	x == STRUCT_LINUX_DIRENT_P || x == STRUCT_MMSGHDR_P ||\
	x == STRUCT_MQ_ATTR_P || x == STRUCT_MSGHDR_P || x == STRUCT_MSQID_DS_P ||\
	x == STRUCT_NFSCTL_ARG_P || x == STRUCT_OLD_LINUX_DIRENT_P ||\
	x == STRUCT_PERF_EVENT_ATTR_P || x == STRUCT_POLLFD_P ||\
	x == STRUCT_RLIMIT_P || x == STRUCT_ROBUST_LIST_HEAD_P ||\
	x == STRUCT_RUSAGE_P || x == STRUCT_SCHED_PARAM_P ||\
	x == STRUCT_SEMBUF_P || x == STRUCT_SHMID_DS_P ||\
	x == STRUCT_SIGACTION_P || x == STRUCT_SIGEVENT_P ||\
	x == STRUCT_SOCKADDR_P || x == STRUCT_STATFS_P || x == STRUCT_STAT_P ||\
	x == STRUCT_SYSINFO_P || x == STRUCT_TIMESPEC_P || x == STRUCT_TIMEVAL_P ||\
	x == STRUCT_TIMEX_P || x == STRUCT_TIMEZONE_P || x == STRUCT_TMS_P ||\
	x == STRUCT_USER_DESC_P || x == STRUCT_USTAT_P || x == STRUCT_UTIMBUF_P ||\
	x == STRUCT_UTSNAME_P || x == STRUCT_VM86_STRUCT_P ||\
	x == STRUCT___SYSCTL_ARGS_P || x == TIMER_T_P || x == TIME_T_P ||\
	x == UID_T_P || x == UNION_NFSCTL_RES_P || x == UNSIGNED_CHAR_P ||\
	x == UNSIGNED_LONG_P || x == UNSIGNED_P || x == VOID_P)

/**
 * struct flag_s - struct that associates a flag macro with its name and value
 * @name: name of flag as a string
 * @value: value of flag
 **/
typedef struct flag_s
{
	const char *name;
	int value;
} flag_t;

/**
 * enum type_e - Enumerates the different types present in the different
 *               syscall parameters and return types
 * @AIO_CONTEXT_T: AIO_CONTEXT_T
 * @AIO_CONTEXT_T_P: AIO_CONTEXT_T_P
 * @CADDR_T: CADDR_T
 * @CAP_USER_DATA_T: CAP_USER_DATA_T
 * @CAP_USER_HEADER_T: CAP_USER_HEADER_T
 * @CHAR_P: CHAR_P
 * @CLOCKID_T: CLOCKID_T
 * @CLOCK_T: CLOCK_T
 * @CPU_SET_T_P: CPU_SET_T_P
 * @DEV_T: DEV_T
 * @ENUM___PTRACE_REQUEST: ENUM___PTRACE_REQUEST
 * @FD_SET_P: FD_SET_P
 * @GID_T: GID_T
 * @GID_T_P: GID_T_P
 * @IDTYPE_T: IDTYPE_T
 * @ID_T: ID_T
 * @INT: INT
 * @INT_P: INT_P
 * @KEY_SERIAL_T: KEY_SERIAL_T
 * @KEY_T: KEY_T
 * @LOFF_T_P: LOFF_T_P
 * @LONG: LONG
 * @LONG_P: LONG_P
 * @MODE_T: MODE_T
 * @MQD_T: MQD_T
 * @NFDS_T: NFDS_T
 * @OFF64_T: OFF64_T
 * @OFF_T: OFF_T
 * @OFF_T_P: OFF_T_P
 * @PID_T: PID_T
 * @SIGHANDLER_T: SIGHANDLER_T
 * @SIGINFO_T_P: SIGINFO_T_P
 * @SIGSET_T_P: SIGSET_T_P
 * @SIZE_T: SIZE_T
 * @SIZE_T_P: SIZE_T_P
 * @SOCKLEN_T: SOCKLEN_T
 * @SOCKLEN_T_P: SOCKLEN_T_P
 * @SSIZE_T: SSIZE_T
 * @STACK_T_P: STACK_T_P
 * @STRUCT_EPOLL_EVENT_P: STRUCT_EPOLL_EVENT_P
 * @STRUCT_GETCPU_CACHE_P: STRUCT_GETCPU_CACHE_P
 * @STRUCT_IOCB_P: STRUCT_IOCB_P
 * @STRUCT_IOCB_PP: STRUCT_IOCB_PP
 * @STRUCT_IOVEC_P: STRUCT_IOVEC_P
 * @STRUCT_IO_EVENT_P: STRUCT_IO_EVENT_P
 * @STRUCT_ITIMERSPEC_P: STRUCT_ITIMERSPEC_P
 * @STRUCT_ITIMERVAL_P: STRUCT_ITIMERVAL_P
 * @STRUCT_KERNEL_SYM_P: STRUCT_KERNEL_SYM_P
 * @STRUCT_KEXEC_SEGMENT_P: STRUCT_KEXEC_SEGMENT_P
 * @STRUCT_LINUX_DIRENT_P: STRUCT_LINUX_DIRENT_P
 * @STRUCT_MMSGHDR_P: STRUCT_MMSGHDR_P
 * @STRUCT_MQ_ATTR_P: STRUCT_MQ_ATTR_P
 * @STRUCT_MSGHDR_P: STRUCT_MSGHDR_P
 * @STRUCT_MSQID_DS_P: STRUCT_MSQID_DS_P
 * @STRUCT_NFSCTL_ARG_P: STRUCT_NFSCTL_ARG_P
 * @STRUCT_OLD_LINUX_DIRENT_P: STRUCT_OLD_LINUX_DIRENT_P
 * @STRUCT_PERF_EVENT_ATTR_P: STRUCT_PERF_EVENT_ATTR_P
 * @STRUCT_POLLFD_P: STRUCT_POLLFD_P
 * @STRUCT_RLIMIT_P: STRUCT_RLIMIT_P
 * @STRUCT_ROBUST_LIST_HEAD_P: STRUCT_ROBUST_LIST_HEAD_P
 * @STRUCT_ROBUST_LIST_HEAD_PP: STRUCT_ROBUST_LIST_HEAD_PP
 * @STRUCT_RUSAGE_P: STRUCT_RUSAGE_P
 * @STRUCT_SCHED_PARAM_P: STRUCT_SCHED_PARAM_P
 * @STRUCT_SEMBUF_P: STRUCT_SEMBUF_P
 * @STRUCT_SHMID_DS_P: STRUCT_SHMID_DS_P
 * @STRUCT_SIGACTION_P: STRUCT_SIGACTION_P
 * @STRUCT_SIGEVENT_P: STRUCT_SIGEVENT_P
 * @STRUCT_SOCKADDR_P: STRUCT_SOCKADDR_P
 * @STRUCT_STATFS_P: STRUCT_STATFS_P
 * @STRUCT_STAT_P: STRUCT_STAT_P
 * @STRUCT_SYSINFO_P: STRUCT_SYSINFO_P
 * @STRUCT_TIMESPEC: STRUCT_TIMESPEC
 * @STRUCT_TIMESPEC_P: STRUCT_TIMESPEC_P
 * @STRUCT_TIMEVAL: STRUCT_TIMEVAL
 * @STRUCT_TIMEVAL_P: STRUCT_TIMEVAL_P
 * @STRUCT_TIMEX_P: STRUCT_TIMEX_P
 * @STRUCT_TIMEZONE_P: STRUCT_TIMEZONE_P
 * @STRUCT_TMS_P: STRUCT_TMS_P
 * @STRUCT_USER_DESC_P: STRUCT_USER_DESC_P
 * @STRUCT_USTAT_P: STRUCT_USTAT_P
 * @STRUCT_UTIMBUF_P: STRUCT_UTIMBUF_P
 * @STRUCT_UTSNAME_P: STRUCT_UTSNAME_P
 * @STRUCT_VM86_STRUCT_P: STRUCT_VM86_STRUCT_P
 * @STRUCT___SYSCTL_ARGS_P: STRUCT___SYSCTL_ARGS_P
 * @TIMER_T: TIMER_T
 * @TIMER_T_P: TIMER_T_P
 * @TIME_T: TIME_T
 * @TIME_T_P: TIME_T_P
 * @U64: U64
 * @UID_T: UID_T
 * @UID_T_P: UID_T_P
 * @UINT32_T: UINT32_T
 * @UNION_NFSCTL_RES_P: UNION_NFSCTL_RES_P
 * @UNSIGNED: UNSIGNED
 * @UNSIGNED_CHAR_P: UNSIGNED_CHAR_P
 * @UNSIGNED_INT: UNSIGNED_INT
 * @UNSIGNED_LONG: UNSIGNED_LONG
 * @UNSIGNED_LONG_P: UNSIGNED_LONG_P
 * @UNSIGNED_P: UNSIGNED_P
 * @VARARGS: VARARGS
 * @VOID: VOID
 * @VOID_P: VOID_P
 * @VOID_PP: VOID_PP
 */
typedef enum type_e
{
	AIO_CONTEXT_T,
	AIO_CONTEXT_T_P,
	CADDR_T,
	CAP_USER_DATA_T,
	CAP_USER_HEADER_T,
	CHAR_P,
	CLOCKID_T,
	CLOCK_T,
	CPU_SET_T_P,
	DEV_T,
	ENUM___PTRACE_REQUEST,
	FD_SET_P,
	GID_T,
	GID_T_P,
	IDTYPE_T,
	ID_T,
	INT,
	INT_P,
	KEY_SERIAL_T,
	KEY_T,
	LOFF_T_P,
	LONG,
	LONG_P,
	MODE_T,
	MQD_T,
	NFDS_T,
	OFF64_T,
	OFF_T,
	OFF_T_P,
	PID_T,
	SIGHANDLER_T,
	SIGINFO_T_P,
	SIGSET_T_P,
	SIZE_T,
	SIZE_T_P,
	SOCKLEN_T,
	SOCKLEN_T_P,
	SSIZE_T,
	STACK_T_P,
	STRUCT_EPOLL_EVENT_P,
	STRUCT_GETCPU_CACHE_P,
	STRUCT_IOCB_P,
	STRUCT_IOCB_PP,
	STRUCT_IOVEC_P,
	STRUCT_IO_EVENT_P,
	STRUCT_ITIMERSPEC_P,
	STRUCT_ITIMERVAL_P,
	STRUCT_KERNEL_SYM_P,
	STRUCT_KEXEC_SEGMENT_P,
	STRUCT_LINUX_DIRENT_P,
	STRUCT_MMSGHDR_P,
	STRUCT_MQ_ATTR_P,
	STRUCT_MSGHDR_P,
	STRUCT_MSQID_DS_P,
	STRUCT_NFSCTL_ARG_P,
	STRUCT_OLD_LINUX_DIRENT_P,
	STRUCT_PERF_EVENT_ATTR_P,
	STRUCT_POLLFD_P,
	STRUCT_RLIMIT_P,
	STRUCT_ROBUST_LIST_HEAD_P,
	STRUCT_ROBUST_LIST_HEAD_PP,
	STRUCT_RUSAGE_P,
	STRUCT_SCHED_PARAM_P,
	STRUCT_SEMBUF_P,
	STRUCT_SHMID_DS_P,
	STRUCT_SIGACTION_P,
	STRUCT_SIGEVENT_P,
	STRUCT_SOCKADDR_P,
	STRUCT_STATFS_P,
	STRUCT_STAT_P,
	STRUCT_SYSINFO_P,
	STRUCT_TIMESPEC,
	STRUCT_TIMESPEC_P,
	STRUCT_TIMEVAL,
	STRUCT_TIMEVAL_P,
	STRUCT_TIMEX_P,
	STRUCT_TIMEZONE_P,
	STRUCT_TMS_P,
	STRUCT_USER_DESC_P,
	STRUCT_USTAT_P,
	STRUCT_UTIMBUF_P,
	STRUCT_UTSNAME_P,
	STRUCT_VM86_STRUCT_P,
	STRUCT___SYSCTL_ARGS_P,
	TIMER_T,
	TIMER_T_P,
	TIME_T,
	TIME_T_P,
	U64,
	UID_T,
	UID_T_P,
	UINT32_T,
	UNION_NFSCTL_RES_P,
	UNSIGNED,
	UNSIGNED_CHAR_P,
	UNSIGNED_INT,
	UNSIGNED_LONG,
	UNSIGNED_LONG_P,
	UNSIGNED_P,
	VARARGS,
	VOID,
	VOID_P,
	VOID_PP
} type_t;

/**
 * struct syscall_s - Stores information about a syscall
 *
 * @name: Name of the syscall
 * @nr: Syscall number in the syscalls table
 * @ret: Return type
 * @nb_params: Number of parameters
 * @params: Array of parameters types
 */
typedef struct syscall_s
{
	char const * const name;
	size_t const nr;
	type_t const ret;
	size_t const nb_params;
	type_t const params[MAX_PARAMS];
} syscall_t;




static syscall_t const syscalls_64_g[] = {
	{"read", 0, SSIZE_T, 3, {INT, VOID_P, SIZE_T, -1, -1, -1}},
	{"write", 1, SSIZE_T, 3, {INT, VOID_P, SIZE_T, -1, -1, -1}},
	{"open", 2, INT, 2, {CHAR_P, INT, -1, -1, -1, -1}},
	{"close", 3, INT, 1, {INT, -1, -1, -1, -1, -1}},
	{"stat", 4, INT, 2, {CHAR_P, STRUCT_STAT_P, -1, -1, -1, -1}},
	{"fstat", 5, INT, 2, {INT, STRUCT_STAT_P, -1, -1, -1, -1}},
	{"lstat", 6, INT, 2, {CHAR_P, STRUCT_STAT_P, -1, -1, -1, -1}},
	{"poll", 7, INT, 3, {STRUCT_POLLFD_P, NFDS_T, INT, -1, -1, -1}},
	{"lseek", 8, OFF_T, 3, {INT, OFF_T, INT, -1, -1, -1}},
	{"mmap", 9, VOID_P, 6, {VOID_P, SIZE_T, INT, INT, INT, OFF_T}},
	{"mprotect", 10, INT, 3, {VOID_P, SIZE_T, INT, -1, -1, -1}},
	{"munmap", 11, INT, 2, {VOID_P, SIZE_T, -1, -1, -1, -1}},
	{"brk", 12, INT, 1, {VOID_P, -1, -1, -1, -1, -1}},
	{"rt_sigaction", 13, INT, 3, {INT, STRUCT_SIGACTION_P,
		STRUCT_SIGACTION_P, -1, -1, -1}},
	{"rt_sigprocmask", 14, INT, 3, {INT, SIGSET_T_P, SIGSET_T_P, -1, -1,
		-1}},
	{"rt_sigreturn", 15, INT, 1, {UNSIGNED_LONG, -1, -1, -1, -1, -1}},
	{"ioctl", 16, INT, 3, {INT, INT, VARARGS, -1, -1, -1}},
	{"pread64", 17, SSIZE_T, 4, {INT, VOID_P, SIZE_T, OFF_T, -1, -1}},
	{"pwrite64", 18, SSIZE_T, 4, {INT, VOID_P, SIZE_T, OFF_T, -1, -1}},
	{"readv", 19, SSIZE_T, 3, {INT, STRUCT_IOVEC_P, INT, -1, -1, -1}},
	{"writev", 20, SSIZE_T, 3, {INT, STRUCT_IOVEC_P, INT, -1, -1, -1}},
	{"access", 21, INT, 2, {CHAR_P, INT, -1, -1, -1, -1}},
	{"pipe", 22, INT, 1, {INT, -1, -1, -1, -1, -1}},
	{"select", 23, INT, 5, {INT, FD_SET_P, FD_SET_P, FD_SET_P,
		STRUCT_TIMEVAL_P, -1}},
	{"sched_yield", 24, INT, 1, {VOID, -1, -1, -1, -1, -1}},
	{"mremap", 25, VOID_P, 5, {VOID_P, SIZE_T, SIZE_T, INT, VARARGS, -1}},
	{"msync", 26, INT, 3, {VOID_P, SIZE_T, INT, -1, -1, -1}},
	{"mincore", 27, INT, 3, {VOID_P, SIZE_T, UNSIGNED_CHAR_P, -1, -1, -1}},
	{"madvise", 28, INT, 3, {VOID_P, SIZE_T, INT, -1, -1, -1}},
	{"shmget", 29, INT, 3, {KEY_T, SIZE_T, INT, -1, -1, -1}},
	{"shmat", 30, VOID_P, 3, {INT, VOID_P, INT, -1, -1, -1}},
	{"shmctl", 31, INT, 3, {INT, INT, STRUCT_SHMID_DS_P, -1, -1, -1}},
	{"dup", 32, INT, 1, {INT, -1, -1, -1, -1, -1}},
	{"dup2", 33, INT, 2, {INT, INT, -1, -1, -1, -1}},
	{"pause", 34, INT, 1, {VOID, -1, -1, -1, -1, -1}},
	{"nanosleep", 35, INT, 2, {STRUCT_TIMESPEC_P, STRUCT_TIMESPEC_P, -1,
		-1, -1, -1}},
	{"getitimer", 36, INT, 2, {INT, STRUCT_ITIMERVAL_P, -1, -1, -1, -1}},
	{"alarm", 37, UNSIGNED_INT, 1, {UNSIGNED_INT, -1, -1, -1, -1, -1}},
	{"setitimer", 38, INT, 3, {INT, STRUCT_ITIMERVAL_P, STRUCT_ITIMERVAL_P,
		-1, -1, -1}},
	{"getpid", 39, PID_T, 1, {VOID, -1, -1, -1, -1, -1}},
	{"sendfile", 40, SSIZE_T, 4, {INT, INT, OFF_T_P, SIZE_T, -1, -1}},
	{"socket", 41, INT, 3, {INT, INT, INT, -1, -1, -1}},
	{"connect", 42, INT, 3, {INT, STRUCT_SOCKADDR_P, SOCKLEN_T, -1, -1,
		-1}},
	{"accept", 43, INT, 3, {INT, STRUCT_SOCKADDR_P, SOCKLEN_T_P, -1, -1,
		-1}},
	{"sendto", 44, SSIZE_T, 6, {INT, VOID_P, SIZE_T, INT,
		STRUCT_SOCKADDR_P, SOCKLEN_T}},
	{"recvfrom", 45, SSIZE_T, 6, {INT, VOID_P, SIZE_T, INT,
		STRUCT_SOCKADDR_P, SOCKLEN_T_P}},
	{"sendmsg", 46, SSIZE_T, 3, {INT, STRUCT_MSGHDR_P, INT, -1, -1, -1}},
	{"recvmsg", 47, SSIZE_T, 3, {INT, STRUCT_MSGHDR_P, INT, -1, -1, -1}},
	{"shutdown", 48, INT, 2, {INT, INT, -1, -1, -1, -1}},
	{"bind", 49, INT, 3, {INT, STRUCT_SOCKADDR_P, SOCKLEN_T, -1, -1, -1}},
	{"listen", 50, INT, 2, {INT, INT, -1, -1, -1, -1}},
	{"getsockname", 51, INT, 3, {INT, STRUCT_SOCKADDR_P, SOCKLEN_T_P, -1,
		-1, -1}},
	{"getpeername", 52, INT, 3, {INT, STRUCT_SOCKADDR_P, SOCKLEN_T_P, -1,
		-1, -1}},
	{"socketpair", 53, INT, 4, {INT, INT, INT, INT, -1, -1}},
	{"setsockopt", 54, INT, 5, {INT, INT, INT, VOID_P, SOCKLEN_T, -1}},
	{"getsockopt", 55, INT, 5, {INT, INT, INT, VOID_P, SOCKLEN_T_P, -1}},
	{"clone", 56, INT, 5, {INT, VOID_P, INT, VOID_P, VARARGS, -1}},
	{"fork", 57, PID_T, 1, {VOID, -1, -1, -1, -1, -1}},
	{"vfork", 58, PID_T, 1, {VOID, -1, -1, -1, -1, -1}},
	{"execve", 59, INT, 3, {CHAR_P, CHAR_P, CHAR_P, -1, -1, -1}},
	{"exit", 60, VOID, 1, {INT, -1, -1, -1, -1, -1}},
	{"wait4", 61, PID_T, 4, {PID_T, INT_P, INT, STRUCT_RUSAGE_P, -1, -1}},
	{"kill", 62, INT, 2, {PID_T, INT, -1, -1, -1, -1}},
	{"uname", 63, INT, 1, {STRUCT_UTSNAME_P, -1, -1, -1, -1, -1}},
	{"semget", 64, INT, 3, {KEY_T, INT, INT, -1, -1, -1}},
	{"semop", 65, INT, 3, {INT, STRUCT_SEMBUF_P, UNSIGNED, -1, -1,
		-1}},
	{"semctl", 66, INT, 4, {INT, INT, INT, VARARGS, -1, -1}},
	{"shmdt", 67, INT, 1, {VOID_P, -1, -1, -1, -1, -1}},
	{"msgget", 68, INT, 2, {KEY_T, INT, -1, -1, -1, -1}},
	{"msgsnd", 69, INT, 4, {INT, VOID_P, SIZE_T, INT, -1, -1}},
	{"msgrcv", 70, SSIZE_T, 5, {INT, VOID_P, SIZE_T, LONG, INT, -1}},
	{"msgctl", 71, INT, 3, {INT, INT, STRUCT_MSQID_DS_P, -1, -1, -1}},
	{"fcntl", 72, INT, 3, {INT, INT, VARARGS, -1, -1, -1}},
	{"flock", 73, INT, 2, {INT, INT, -1, -1, -1, -1}},
	{"fsync", 74, INT, 1, {INT, -1, -1, -1, -1, -1}},
	{"fdatasync", 75, INT, 1, {INT, -1, -1, -1, -1, -1}},
	{"truncate", 76, INT, 2, {CHAR_P, OFF_T, -1, -1, -1, -1}},
	{"ftruncate", 77, INT, 2, {INT, OFF_T, -1, -1, -1, -1}},
	{"getdents", 78, INT, 3, {UNSIGNED_INT, STRUCT_LINUX_DIRENT_P,
		UNSIGNED_INT, -1, -1, -1}},
	{"getcwd", 79, CHAR_P, 2, {CHAR_P, SIZE_T, -1, -1, -1, -1}},
	{"chdir", 80, INT, 1, {CHAR_P, -1, -1, -1, -1, -1}},
	{"fchdir", 81, INT, 1, {INT, -1, -1, -1, -1, -1}},
	{"rename", 82, INT, 2, {CHAR_P, CHAR_P, -1, -1, -1, -1}},
	{"mkdir", 83, INT, 2, {CHAR_P, MODE_T, -1, -1, -1, -1}},
	{"rmdir", 84, INT, 1, {CHAR_P, -1, -1, -1, -1, -1}},
	{"creat", 85, INT, 2, {CHAR_P, MODE_T, -1, -1, -1, -1}},
	{"link", 86, INT, 2, {CHAR_P, CHAR_P, -1, -1, -1, -1}},
	{"unlink", 87, INT, 1, {CHAR_P, -1, -1, -1, -1, -1}},
	{"symlink", 88, INT, 2, {CHAR_P, CHAR_P, -1, -1, -1, -1}},
	{"readlink", 89, SSIZE_T, 3, {CHAR_P, CHAR_P, SIZE_T, -1, -1, -1}},
	{"chmod", 90, INT, 2, {CHAR_P, MODE_T, -1, -1, -1, -1}},
	{"fchmod", 91, INT, 2, {INT, MODE_T, -1, -1, -1, -1}},
	{"chown", 92, INT, 3, {CHAR_P, UID_T, GID_T, -1, -1, -1}},
	{"fchown", 93, INT, 3, {INT, UID_T, GID_T, -1, -1, -1}},
	{"lchown", 94, INT, 3, {CHAR_P, UID_T, GID_T, -1, -1, -1}},
	{"umask", 95, MODE_T, 1, {MODE_T, -1, -1, -1, -1, -1}},
	{"gettimeofday", 96, INT, 2, {STRUCT_TIMEVAL_P, STRUCT_TIMEZONE_P, -1,
		-1, -1, -1}},
	{"getrlimit", 97, INT, 2, {INT, STRUCT_RLIMIT_P, -1, -1, -1, -1}},
	{"getrusage", 98, INT, 2, {INT, STRUCT_RUSAGE_P, -1, -1, -1, -1}},
	{"sysinfo", 99, INT, 1, {STRUCT_SYSINFO_P, -1, -1, -1, -1, -1}},
	{"times", 100, CLOCK_T, 1, {STRUCT_TMS_P, -1, -1, -1, -1, -1}},
??? from here until ???END lines may have been inserted/deleted
	{"ptrace", 101, LONG, 4, {ENUM___PTRACE_REQUEST, PID_T, VOID_P,
		VOID_P, -1, -1}},
	{"getuid", 102, UID_T, 1, {VOID, -1, -1, -1, -1, -1}},
	{"syslog", 103, INT, 3, {INT, CHAR_P, INT, -1, -1, -1}},
	{"getgid", 104, GID_T, 1, {VOID, -1, -1, -1, -1, -1}},
	{"setuid", 105, INT, 1, {UID_T, -1, -1, -1, -1, -1}},
	{"setgid", 106, INT, 1, {GID_T, -1, -1, -1, -1, -1}},
	{"geteuid", 107, UID_T, 1, {VOID, -1, -1, -1, -1, -1}},
	{"getegid", 108, GID_T, 1, {VOID, -1, -1, -1, -1, -1}},
	{"setpgid", 109, INT, 2, {PID_T, PID_T, -1, -1, -1, -1}},
	{"getppid", 110, PID_T, 1, {VOID, -1, -1, -1, -1, -1}},
	{"getpgrp", 111, PID_T, 1, {VOID, -1, -1, -1, -1, -1}},
	{"setsid", 112, PID_T, 1, {VOID, -1, -1, -1, -1, -1}},
	{"setreuid", 113, INT, 2, {UID_T, UID_T, -1, -1, -1, -1}},
	{"setregid", 114, INT, 2, {GID_T, GID_T, -1, -1, -1, -1}},
	{"getgroups", 115, INT, 2, {INT, GID_T, -1, -1, -1, -1}},
	{"setgroups", 116, INT, 2, {SIZE_T, GID_T_P, -1, -1, -1, -1}},
	{"setresuid", 117, INT, 3, {UID_T, UID_T, UID_T, -1, -1, -1}},
	{"getresuid", 118, INT, 3, {UID_T_P, UID_T_P, UID_T_P, -1, -1, -1}},
	{"setresgid", 119, INT, 3, {GID_T, GID_T, GID_T, -1, -1, -1}},
	{"getresgid", 120, INT, 3, {GID_T_P, GID_T_P, GID_T_P, -1, -1, -1}},
	{"getpgid", 121, PID_T, 1, {PID_T, -1, -1, -1, -1, -1}},
	{"setfsuid", 122, INT, 1, {UID_T, -1, -1, -1, -1, -1}},
	{"setfsgid", 123, INT, 1, {UID_T, -1, -1, -1, -1, -1}},
	{"getsid", 124, PID_T, 1, {PID_T, -1, -1, -1, -1, -1}},
	{"capget", 125, INT, 2, {CAP_USER_HEADER_T, CAP_USER_DATA_T, -1, -1,
		-1, -1}},
	{"capset", 126, INT, 2, {CAP_USER_HEADER_T, CAP_USER_DATA_T, -1, -1,
		-1, -1}},
	{"rt_sigpending", 127, INT, 1, {SIGSET_T_P, -1, -1, -1, -1, -1}},
	{"rt_sigtimedwait", 128, INT, 3, {SIGSET_T_P, SIGINFO_T_P,
		STRUCT_TIMESPEC_P, -1, -1, -1}},
	{"rt_sigqueueinfo", 129, INT, 3, {PID_T, INT, SIGINFO_T_P, -1, -1, -1}},
	{"rt_sigsuspend", 130, INT, 1, {SIGSET_T_P, -1, -1, -1, -1, -1}},
	{"sigaltstack", 131, INT, 2, {STACK_T_P, STACK_T_P, -1, -1, -1, -1}},
	{"utime", 132, INT, 2, {CHAR_P, STRUCT_UTIMBUF_P, -1, -1, -1, -1}},
	{"mknod", 133, INT, 3, {CHAR_P, MODE_T, DEV_T, -1, -1, -1}},
	{"uselib", 134, INT, 1, {CHAR_P, -1, -1, -1, -1, -1}},
	{"personality", 135, INT, 1, {UNSIGNED_LONG, -1, -1, -1, -1, -1}},
	{"ustat", 136, INT, 2, {DEV_T, STRUCT_USTAT_P, -1, -1, -1, -1}},
	{"statfs", 137, INT, 2, {CHAR_P, STRUCT_STATFS_P, -1, -1, -1, -1}},
	{"fstatfs", 138, INT, 2, {INT, STRUCT_STATFS_P, -1, -1, -1, -1}},
	{"sysfs", 139, INT, 2, {INT, CHAR_P, -1, -1, -1, -1}},
	{"getpriority", 140, INT, 2, {INT, INT, -1, -1, -1, -1}},
	{"setpriority", 141, INT, 3, {INT, INT, INT, -1, -1, -1}},
	{"sched_setparam", 142, INT, 2, {PID_T, STRUCT_SCHED_PARAM_P, -1, -1,
		-1, -1}},
	{"sched_getparam", 143, INT, 2, {PID_T, STRUCT_SCHED_PARAM_P, -1, -1,
		-1, -1}},
	{"sched_setscheduler", 144, INT, 3, {PID_T, INT, STRUCT_SCHED_PARAM_P,
		-1, -1, -1}},
	{"sched_getscheduler", 145, INT, 1, {PID_T, -1, -1, -1, -1, -1}},
	{"sched_get_priority_max", 146, INT, 1, {INT, -1, -1, -1, -1, -1}},
	{"sched_get_priority_min", 147, INT, 1, {INT, -1, -1, -1, -1, -1}},
	{"sched_rr_get_interval", 148, INT, 2, {PID_T, STRUCT_TIMESPEC_P, -1,
		-1, -1, -1}},
	{"mlock", 149, INT, 2, {VOID_P, SIZE_T, -1, -1, -1, -1}},
	{"munlock", 150, INT, 2, {VOID_P, SIZE_T, -1, -1, -1, -1}},
	{"mlockall", 151, INT, 1, {INT, -1, -1, -1, -1, -1}},
	{"munlockall", 152, INT, 1, {VOID, -1, -1, -1, -1, -1}},
	{"vhangup", 153, INT, 1, {VOID, -1, -1, -1, -1, -1}},
	{"modify_ldt", 154, INT
???END
