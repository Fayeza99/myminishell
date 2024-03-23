/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:23:08 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/23 17:33:36 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"



char	getcharacter(t_lexer *lexer)
{
	return(*lexer->current++);
}

char	peekcharacter(t_lexer *lexer)
{
	return (*lexer->current);
}

t_lexer	create_lexer(const char *s)
{
	t_lexer lexer;
	lexer.current = s;
	return (lexer);
}

t_lexeme	*create_lexeme(t_tokens token, char *s, size_t len)
{
	t_lexeme *lex;

	lex  = (t_lexeme *)malloc (sizeof(t_lexeme));
	lex->token = token;
	lex->str = new_string(s, len);
	return (lex);
}

int		is_whitespace(char c)
{
	return ((c >= 9 && c < 14) || c == 32);
}

int		is_identifier(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int		is_less(char c) {
	return (c == '<');
}

int		is_greater(char c) {
	return (c == '>');
}


int		is_pipes(char c) {
	return (c == '|');
}


int		is_dash(char c) {
	return (c == '-');
}


int		is_expansion(char c) {
	return (c == '$');
}


int		is_EOF(char c) {
	return (c == '\0');
}

const char *get_token_name(t_tokens token)
{
	char *names[] = {
		"IDEFNTIFIERS",
		"LESS", 
		"GREATER",
		"EXPANSION",
		"PIPES",
		"DASH",
		"UNEXPECTED",
		"END_OF_FILE"
	};
	return (names[token]);
}