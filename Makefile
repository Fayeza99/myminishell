NAME		=	minishell
CFLAGS		=	-Wall -Wextra -Werror -Ofast
RL			=	-lreadline
LIBFT_PATH	=	include/libft
LIBFT		=	$(LIBFT_PATH)/libft.a

PARSE		=	lst_parse/args.c lst_parse/args2.c lst_parse/error_flag.c lst_parse/free.c\
				lst_parse/init.c lst_parse/read_cmd.c lst_parse/parse.c lst_parse/get_fd.c\
				env/env_help.c env/ft_env.c lst_parse/errors.c\
				utils/arrays.c utils/utils.c utils/testing.c utils/ft_lst.c
EXEC		=	exec/export.c exec/executions.c exec/executions2.c\
				exec/executions3.c exec/executions4.c exec/builtins.c\
				exec/unset.c exec/exit.c
SRC			=	main.c signals.c $(PARSE) $(EXEC)

all: $(NAME)

$(NAME): $(LIBFT) $(SRC)
	cc $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT) $(RL)

$(LIBFT):
	make all bonus -sC $(LIBFT_PATH)

clean:
	make clean -sC $(LIBFT_PATH)

fclean: clean
	make fclean -sC $(LIBFT_PATH)
	rm -rf $(NAME)

re: fclean all

.PHONY: all lib clean fclean re