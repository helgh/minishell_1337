# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/27 22:23:59 by hael-ghd          #+#    #+#              #
#    Updated: 2024/08/19 21:14:55 by hael-ghd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

SOURCE = main.c ./parse/check_qoutes.c ./parse/expantion.c ./parse/expantion_utils.c ./parse/spl_and_replace.c ./parse/syntax_error.c \
			./parse/tokenizer.c ./parse/tokenizer_utils.c ./garbage/garbage_collector.c ./libft_function/itoa.c ./libft_function/join_str.c \
			./libft_function/split.c ./libft_function/str_dup.c ./libft_function/strcmp.c ./libft_function/strlen.c ./libft_function/strncmp.c \
			./libft_function/ft_isalpha.c ./libft_function/ft_isdigit.c ./libft_function/ft_isprint.c free_memory.c \

OBJ_SRC = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_SRC)
	@$(CC) $(FLAGS) -lreadline -o $(NAME) $(OBJ_SRC)

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "Cleaning"
	@rm -f $(OBJ_SRC)

fclean: clean
	@rm -f $(NAME)

re: fclean all
