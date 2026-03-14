CC      = gcc
CFLAGS  = -Wall -Werror -Wextra -pedantic
RM      = rm -f

# Binaries
NAME0   = strace_0
NAME1   = strace_1
NAME2   = strace_2
NAME3   = strace_3


# Sources
SRC0    = strace_0.c
SRC1    = strace_1.c
SRC2    = strace_2.c
SRC3    = strace_3.c

# Phony targets (not files)
.PHONY: all clean fclean re strace_0 strace_1 strace_2

# Default target builds everything
all: $(NAME0) $(NAME1) $(NAME2)

# Specific rules for each version
$(NAME0): $(SRC0)
	$(CC) $(CFLAGS) $(SRC0) -o $(NAME0)

$(NAME1): $(SRC1) syscalls.h
	$(CC) $(CFLAGS) $(SRC1) -o $(NAME1)

$(NAME2): $(SRC2) syscalls.h
	$(CC) $(CFLAGS) $(SRC2) -o $(NAME2)

$(NAME3): $(SRC3) syscalls.h
	$(CC) $(CFLAGS) $(SRC2) -o $(NAME3)

# Explicit rule aliases for the checker
strace_0: $(NAME0)
strace_1: $(NAME1)
strace_2: $(NAME2)
strace_3: $(NAME3)

# Cleanup rules
clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME0) $(NAME1) $(NAME2) $(NAME3)

re: fclean all
