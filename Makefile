# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/27 22:23:59 by hael-ghd          #+#    #+#              #
#    Updated: 2024/07/30 09:29:14 by hael-ghd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = CC

FLAGS = -Wall -Wextra -Werror

SOURCE = main.c ft_strcmp.c ft_split.c \

OBJ_SRC = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_SRC)
	$(CC) $(FLAGS) $(OBJ_SRC) -lreadline -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $<

clean:
	rm -f $(OBJ_SRC)

fclean: clean
	rm -f $(NAME)

re: fclean all
