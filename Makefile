# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/27 22:23:59 by hael-ghd          #+#    #+#              #
#    Updated: 2024/08/15 06:29:31 by hael-ghd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./libft_mini_shell/libft.a

CC = cc

FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

SOURCE = main.c ft_split.c \

OBJ_SRC = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_SRC)
	@$(CC) $(FLAGS) $(LIBFT) $(OBJ_SRC) -lreadline -o $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft_mini_shell
	@echo "Success"

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $<

clean:
	@echo "Cleaning"
	@rm -f $(OBJ_SRC)
	@rm -f ./libft_mini_shell/*.o

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all
