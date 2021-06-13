# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/07 18:20:56 by zqadiri           #+#    #+#              #
#    Updated: 2021/06/13 16:54:12 by zqadiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifneq (,$(findstring xterm,${TERM}))
	GREEN := $(shell tput -Txterm setaf 2)
	YELLOW       := $(shell tput -Txterm setaf 3)
	PURPLE       := $(shell tput -Txterm setaf 5)
	RESET := $(shell tput -Txterm sgr0)
else
	GREEN := ""
	RESET := ""
endif

NAME = pipex

SRCS = 	./src/pipex.c \
		./src/helpers.c \
		./src/exec.c \
		./src/errors.c

OBJS = $(SRCS:.c=.o)

FLAGS= -Wall -Wextra -Werror -g 
RM = rm -f
CC = gcc

UTILS_PATH = ./utils

all: $(NAME)

$(NAME): utils_all
	@cp ./utils/utils.a .
	@$(CC) $(FLAGS) $(SRCS) utils.a -o $(NAME)
	@echo "${YELLOW}Building pipex ...${RESET}"

clean: utils_clean
	@$(RM) utils.a 
	@$(RM) $(OBJS)
	@echo "${PURPLE}Deleting object files ...${RESET}"

fclean: clean utils_fclean
	@$(RM) $(NAME)
	@echo "${PURPLE}Clean executable${RESET}"

re: fclean all

utils_all:
				@make -C $(UTILS_PATH) all
				@cp ./utils/utils.a utils.a
utils_clean:
				@make -C $(UTILS_PATH) clean
utils_fclean:
				@make -C $(UTILS_PATH) fclean
				@$(RM) utils.a
