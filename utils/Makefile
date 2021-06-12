# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 12:11:32 by zqadiri           #+#    #+#              #
#    Updated: 2021/06/12 11:39:51 by zqadiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = utils.a
AR = ar
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

SRC = *.c

all:	$(NAME)

$(NAME): 
		$(CC) $(CFLAGS) -c $(SRC)
	 	$(AR) rsc $(NAME) $(OBJ)
		ranlib $(NAME)
clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)
re:		fclean all
