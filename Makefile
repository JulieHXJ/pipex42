# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 15:04:21 by xhuang            #+#    #+#              #
#    Updated: 2024/12/01 15:51:32 by xhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

RM = rm -f

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c pipex_prep.c pipex_utils.c

SRCOBJ := $(SRCS:%.c=%.o) 

LIBFT = libft/libft.a

.PHONY: all clean fclean re libft

all:	libft $(NAME)

libft: 
	@make -C libft/

$(NAME):	$(SRCOBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCOBJ) -Llibft -lft -o $(NAME)
	@echo "Library $(NAME) has been created."

%.o:	%.c
	@$(CC) $(CFLAGS) -Ilibft -c $< -o $@ 

clean:	
	$(RM) $(SRCOBJ) 
	make clean -C libft
	@echo "Object files have been deleted."

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft
	@echo "Library has been deleted."

re: fclean all 
