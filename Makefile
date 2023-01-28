SRCS = 	srcs/main.c \
		srcs/checks.c \
		srcs/gets.c \
		libft/ft_split.c \
		libft/ft_strdup.c \
		libft/ft_strjoin.c \
		libft/ft_strlen.c \
		libft/ft_strncmp.c \
		libft/ft_strnstr.c \
		libft/ft_substr.c \

CFLAGS = -Wall -Wextra -Werror
NAME = pipex
O_SRCS = $(SRCS:%.c=%.o)
RM = rm -rf
CC = cc

all: $(NAME)

$(NAME): $(O_SRCS)
	$(CC) $(SRCS) -o $(NAME)

clean:
	$(RM) $(O_SRCS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re