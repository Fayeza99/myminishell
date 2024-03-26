/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:58:06 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/25 14:54:05 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "include/libft/libft.h"
# include "string.h"
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


typedef struct s_lexeme
{
	t_tokens	token;
	t_string	str;
} t_lexeme;

typedef struct s_list_lexeme
{
	t_list	*first;
	
}	t_list_lexeme;

typedef struct s_lexer
{
	const char *current;
} t_lexer;

char	getcharacter(t_lexer *lexer);
char	peekcharacter(t_lexer *lexer);
t_lexer	create_lexer(const char *s);
int		is_identifier(char c);

t_lexeme	*create_lexeme(t_tokens token, char *s, size_t len);
int		is_whitespace(char c);
int		is_less(char c);
int		is_greater(char c);
int		is_pipes(char c);
int		is_dash(char c);
int		is_expansion(char c);
int		is_EOF(char c);
int		is_double_quotes(char c);
int		is_single_quotes(char c);




const char *get_token_name(t_tokens token);

#endif