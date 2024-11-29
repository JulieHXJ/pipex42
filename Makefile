# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 15:04:21 by xhuang            #+#    #+#              #
#    Updated: 2024/11/28 19:06:57 by xhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

RM = rm -f

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c pipex_prep.c pipex_utils.c

SRCOBJ := $(SRCS:%.c=%.o) 


.PHONY: all clean fclean re libft

all:	$(NAME)

libft: 
	@make -C libft/

$(NAME):	$(SRCOBJ) 
	ar rcs $(NAME) $(SRCOBJ)
	@echo "Library $(NAME) has been created."

%.o:	%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -Ilibft -c $< -o $@ 

clean:	
	$(RM) $(SRCOBJ) 
	make clean -C libft
	@echo "Object files have been deleted."

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft
	@echo "Library has been deleted."

re: fclean all 
