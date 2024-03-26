/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:58:06 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/26 10:43:12 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../include/libft/libft.h"
# include "../string.h"
# include <stdlib.h>

typedef enum e_tokens
{
	IDENTIFIERS,
	LESS,
	GREATER,
	EXPANSION,
	PIPES,
	DASH,
	D_QUOTES,
	S_QUOTES,
	UNEXPECTED,
	END_OF_FILE,
}	t_tokens;

// contains one argument and its token
typedef struct s_lexeme
{
	t_tokens	token;
	t_string	str;
}	t_lexeme;

// contains the list of arguments
typedef struct s_list_lexeme
{
	t_list		*first;
}	t_list_lexeme;

// contains the input string
typedef struct s_lexer
{
	const char	*current;
}	t_lexer;

void			add_tokens(t_list_lexeme *list, t_lexer *lexer);

char			*getcharacter(t_lexer *lexer);
char			peekcharacter(t_lexer *lexer);
void			add_to_lex(t_list_lexeme *list, t_lexeme *lex);
void			identifier(t_list_lexeme *list, t_lexer *lexer);
void			quoted_str(t_list_lexeme *list, t_lexer *lexer);
void			s_quoted_str(t_list_lexeme *list, t_lexer *lexer);
t_lexer			create_lexer(const char *s);
t_lexeme		*create_lexeme(t_tokens token, char *s, size_t len);
t_list_lexeme	*create_list();
void			delete_list(t_list_lexeme *list);

int				is_identifier(char c);
int				is_whitespace(char c);
int				is_less(char c);
int				is_greater(char c);
int				is_pipes(char c);
int				is_dash(char c);
int				is_expansion(char c);
int				is_EOF(char c);
int				is_double_quotes(char c);
int				is_single_quotes(char c);

const char		*get_token_name(t_tokens token);

#endif