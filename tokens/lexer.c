/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:23:08 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/26 10:41:15 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// return the current char and skip to the next
char	*getcharacter(t_lexer *lexer)
{
	return ((char *)lexer->current++);
}

// return the current char
char	peekcharacter(t_lexer *lexer)
{
	return (*lexer->current);
}

// create a struct for the string to scan through
t_lexer	create_lexer(const char *s)
{
	t_lexer lexer;
	lexer.current = s;
	return (lexer);
}

// create a string-token tuple
t_lexeme	*create_lexeme(t_tokens token, char *s, size_t len)
{
	t_lexeme *lex;

	lex = (t_lexeme *)malloc(sizeof(t_lexeme));
	lex->token = token;
	lex->str = new_string(s, len);
	return (lex);
}

const char	*get_token_name(t_tokens token)
{
	char	*names[] =
	{
		"IDEFNTIFIERS",
		"LESS", 
		"GREATER",
		"EXPANSION",
		"PIPES",
		"DASH",
		"D_QUOTES",
		"S_QUOTES",
		"UNEXPECTED",
		"END_OF_FILE"
	};
	return (names[token]);
}

