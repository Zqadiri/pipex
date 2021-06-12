# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/07 18:20:56 by zqadiri           #+#    #+#              #
#    Updated: 2021/06/12 11:45:26 by zqadiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = 	pipex.c \
		helpers.c \
		exec.c

OBJS = $(SRCS:.c=.o)

FLAGS= -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -f
CC = gcc

UTILS_PATH = ./utils

all: $(NAME)

$(NAME): utils_all
	cp ./utils/utils.a .
	$(CC) $(FLAGS) $(SRCS) utils.a -o $(NAME)

clean: utils_clean
	$(RM) utils.a 
	$(RM) $(OBJS)

fclean: clean utils_fclean
	$(RM) $(NAME)

re: fclean all

utils_all:
			make -C $(UTILS_PATH) all
			cp ./utils/utils.a utils.a
utils_clean:
				make -C $(UTILS_PATH) clean
utils_fclean:
				make -C $(UTILS_PATH) fclean
				$(RM) utils.a
