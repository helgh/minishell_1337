# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/27 22:23:59 by hael-ghd          #+#    #+#              #
#    Updated: 2024/09/24 22:13:55 by hael-ghd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

READ = $(shell brew --prefix readline)/lib

inc = $(shell brew --prefix readline)/include

FLAGS = -Wall -Wextra -Werror

SOURCE = main.c free_and_error.c convert_to_arr.c init_struct.c ./parse/check_qoutes.c ./parse/expantion.c ./parse/expantion_0.c ./parse/expantion_1.c ./parse/expantion_2.c ./parse/expantion_3.c ./parse/spl_and_replace.c ./parse/syntax_error.c \
			./parse/tokenizer.c ./parse/tokenizer_utils.c ./parse/herdoc.c ./parse/herdoc_utils.c ./garbage/garbage_collector.c ./libft_function/itoa.c ./libft_function/join_str.c \
			./libft_function/split.c ./libft_function/ft_atoi.c ./libft_function/ft_put_str.c ./libft_function/ft_strnstr.c ./libft_function/str_dup.c ./libft_function/strcmp.c ./libft_function/strlen.c ./libft_function/strncmp.c \
			./libft_function/ft_isalpha.c ./libft_function/ft_isdigit.c ./libft_function/ft_isalnum.c ./libft_function/ft_isprint.c ./libft_function/ft_my_split.c \
			./libft_function/ft_strjoin.c ./libft_function/ft_strjoin_env.c ./libft_function/sub_str.c ./signals/signal_loop.c ./signals/signal_herdoc.c ./builtins/env.c ./builtins/cd.c ./builtins/cd_contu.c ./builtins/echo.c ./builtins/export.c \
			 ./builtins/pwd.c ./builtins/unset.c ./builtins/shell_lvl.c ./builtins/export_0.c ./builtins/export_1.c ./builtins/exit.c ./builtins/exit_1.c ./execution/open_files.c ./execution/access.c ./execution/_exec.c ./execution/exit_status.c ./execution/dup_files.c
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
