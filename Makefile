NAME		=	minishell
CFLAGS		=	-Wall -Wextra -Werror -Ofast
RL			=	-lreadline
LIBFT_PATH	=	include/libft
LIBFT		=	$(LIBFT_PATH)/libft.a

PARSE		=	parse/args.c parse/args2.c parse/complete_cmd.c parse/free.c\
				parse/init.c parse/parse.c\
				env/env_help.c env/ft_env.c\
				utils/arrays.c utils/utils.c utils/testing.c
EXEC		=	exec/export.c exec/executions.c exec/executions2.c exec/executions3.c
SRC			=	main.c $(PARSE) $(EXEC)

all: $(NAME)

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