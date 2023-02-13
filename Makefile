SRCS = 	srcs/main.c \
		srcs/checks.c \
		srcs/forks.c \
		srcs/gets.c \
		libft/ft_split.c \
		libft/ft_strdup.c \
		libft/ft_strjoin.c \
		libft/ft_strlen.c \
		libft/ft_strncmp.c \
		libft/ft_strnstr.c \
		libft/ft_substr.c \
		libft/ft_putstr.c \

SRCS_B = 	bonus/main_bonus.c \
		bonus/checks_bonus.c \
		bonus/forks_bonus.c \
		bonus/utiles1_bonus.c \
		bonus/gets_bonus.c \
		libft/ft_split.c \
		libft/ft_strdup.c \
		libft/ft_strjoin.c \
		libft/ft_strlen.c \
		libft/ft_strncmp.c \
		libft/ft_strnstr.c \
		libft/ft_substr.c \
		libft/ft_putstr.c \

# CFLAGS = -Wall -Wextra -Werror
NAME = pipex
O_SRCS = $(SRCS:%.c=%.o)
O_SRCS_B = $(SRCS_B:%.c=%.o)
RM = rm -rf
CC = cc

all: $(NAME)

$(NAME): $(O_SRCS)
	$(CC) $(SRCS) -o $(NAME)

bonus: $(O_SRCS_B)
	$(CC) $(SRCS_B) -o $(NAME)

clean:
	$(RM) $(O_SRCS) $(O_SRCS_B)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re