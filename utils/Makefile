# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 12:11:32 by zqadiri           #+#    #+#              #
#    Updated: 2021/06/12 12:26:23 by zqadiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = utils.a
AR = ar
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

SRC = 	ft_calloc.c \
		ft_split.c \
		ft_strjoin.c \
		ft_strncmp.c \
		ft_bzero.c \
		ft_putendl_fd.c \
		ft_strdup.c \
		ft_strlen.c \
		ft_substr.c 

all:	$(NAME)

$(NAME): 
		@$(CC) $(CFLAGS) -c $(SRC)
	 	@$(AR) rsc $(NAME) $(OBJ)
		@ranlib $(NAME)
clean:
		@rm -rf $(OBJ)

fclean: clean
		@rm -rf $(NAME)
re:		fclean all
