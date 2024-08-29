# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/27 22:23:59 by hael-ghd          #+#    #+#              #
#    Updated: 2024/08/29 03:40:36 by hael-ghd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

READ = $(shell brew --prefix readline)/lib

inc = $(shell brew --prefix readline)/include

FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

SOURCE = main.c ./parse/check_qoutes.c ./parse/expantion.c ./parse/expantion_utils.c ./parse/spl_and_replace.c ./parse/syntax_error.c \
			./parse/tokenizer.c ./parse/tokenizer_utils.c ./parse/herdoc.c ./parse/expantion_utils1.c ./garbage/garbage_collector.c ./libft_function/itoa.c ./libft_function/join_str.c \
			./libft_function/split.c ./libft_function/str_dup.c ./libft_function/strcmp.c ./libft_function/strlen.c ./libft_function/strncmp.c \
			./libft_function/ft_isalpha.c ./libft_function/ft_isdigit.c ./libft_function/ft_isprint.c ./libft_function/ft_my_split.c free_memory.c \
			./libft_function/ft_strjoin.c ./libft_function/sub_str.c ./signals/signal_loop.c ./signals/signal_herdoc.c #./builtins/env.c 
OBJ_SRC = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_SRC)
	@$(CC) $(FLAGS) -o $(NAME) -L $(READ) -lreadline $(OBJ_SRC)

%.o: %.c minishell.h
	$(CC) $(FLAGS) -I $(inc) -c $< -o $@

clean:
	@echo "Cleaning"
	@rm -f $(OBJ_SRC)

fclean: clean
	@rm -f $(NAME)

re: fclean all
