CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
SRC = strace_0.c
OBJ = $(SRC:.c=.o)
NAME = strace_0

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

strace_0: all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
