# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/18 15:43:34 by mthamir           #+#    #+#              #
#    Updated: 2024/08/19 16:45:26 by mthamir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mini

CC = cc

FLAGS = -Wall -Wextra -Werror  #-fsanitize=address

SOURCE = ft_my_split.c utils.c env.c main.c 

OBJ_SRC = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME):  $(OBJ_SRC)
	@$(CC) $(FLAGS) mini.h -lreadline $(OBJ_SRC) 

%.o: %.c 
	$(CC) $(FLAGS) -c $<

clean:
	@echo "Cleaning"
	@rm -f $(OBJ_SRC)

fclean: clean
	@rm -f a.out

re: fclean all
