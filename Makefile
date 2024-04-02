# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 15:14:32 by asemsey           #+#    #+#              #
#    Updated: 2024/04/02 18:52:40 by asemsey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CFLAGS		=	-Wall -Wextra -Werror -Ofast
RL			=	-lreadline
LIBFT_PATH	=	include/libft
LIBFT		=	$(LIBFT_PATH)/libft.a
SRC			=	main.c parse.c init.c complete_cmd.c helpers/arrays.c\
				helpers/other.c helpers/args.c helpers/args2.c\
				executions.c export.c executions2.c env.c
# tokens/add_tokens.c tokens/char_types1.c tokens/char_types2.c
# tokens/lexer.c tokens/lexeme.c tokens/quotes.c

all : $(NAME)

$(NAME): lib
	cc $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT) $(RL)


lib:
	make all bonus -sC $(LIBFT_PATH)

clean:
	make clean -sC $(LIBFT_PATH)

fclean: clean
	make fclean -sC $(LIBFT_PATH)
	rm -rf $(NAME)

re: fclean all

.PHONY: all lib clean fclean re