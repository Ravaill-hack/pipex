NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_FILES =  \
	main.c

OBJS = $(SRCS_FILES:.c=.o)

all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
