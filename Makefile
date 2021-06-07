# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/07 18:20:56 by zqadiri           #+#    #+#              #
#    Updated: 2021/06/07 19:26:35 by zqadiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = 	pipex.c \
		helpers.c

OBJS = $(SRCS:.c=.o)

FLAGS= -Wall -Wextra -Werror
RM = rm -f
CC = gcc

LIBFT_PATH = ./libft

all: $(NAME)

$(NAME): libft_all
	@cp ./libft/libft.a .
	@$(CC) $(FLAGS) $(SRCS) libft.a -o $(NAME)

clean:
	@$(RM) libft.a
	@$(RM) $(OBJS)
fclean: clean
	@$(RM) $(NAME)

re: fclean all

libft_all:
				make -C $(LIBFT_PATH) all
				cp ./libft/libft.a libft.a
libft_clean:
				make -C $(LIBFT_PATH) clean
libft_fclean:
				make -C $(LIBFT_PATH) fclean
				$(RM) libft.a