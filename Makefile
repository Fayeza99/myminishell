# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 15:14:32 by asemsey           #+#    #+#              #
#    Updated: 2024/03/23 17:27:18 by fnikzad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRC			=	main.c lexer.c string.c
CFLAGS		=	-Wall -Wextra -Werror
RL			=	-l readline
LIBFT_PATH	=	include/libft
LIBFT		=	$(LIBFT_PATH)/libft.a

all : $(NAME)

$(NAME): lib
	cc $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT) $(RL) -fsanitize=address

lib:
	make all bonus -sC $(LIBFT_PATH)

clean:
	make clean -sC $(LIBFT_PATH)

fclean: clean
	make fclean -sC $(LIBFT_PATH)
	rm -rf $(NAME)

re: fclean all

.PHONY: all lib clean fclean re