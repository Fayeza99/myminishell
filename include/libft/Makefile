NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

SOURCES = ft_isascii.c ft_memcpy.c ft_putstr_fd.c ft_strlcat.c ft_strrchr.c ft_atoi.c\
ft_isdigit.c ft_memmove.c ft_split.c ft_strlcpy.c ft_strtrim.c ft_bzero.c ft_isprint.c\
ft_memset.c ft_strchr.c ft_strlen.c ft_substr.c ft_calloc.c ft_itoa.c ft_putchar_fd.c\
ft_strdup.c ft_strmapi.c ft_tolower.c ft_isalnum.c ft_memchr.c ft_putendl_fd.c\
ft_striteri.c ft_strncmp.c ft_toupper.c ft_isalpha.c ft_memcmp.c ft_putnbr_fd.c\
ft_strjoin.c ft_strnstr.c \
ft_isspace.c ft_argv.c ft_strcmp.c

OBJ = $(SOURCES:.c=.o)

BONUSS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c 

BONUSO = $(BONUSS:.c=.o)

all:	$(NAME)

$(NAME):$(OBJ) 
		ar crs $(NAME) $(OBJ)

%.o: %.c
		cc $(CFLAGS) -c $< -o $@

bonus: $(BONUSO)
		ar crs $(NAME) $(BONUSO)
clean:
		rm -f $(OBJ) $(BONUSO)
fclean:
		rm -f $(OBJ) $(NAME) $(BONUSO)

re: fclean all

.PHONY: re fclean clean bonus all