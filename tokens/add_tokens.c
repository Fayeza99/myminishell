/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:55:42 by asemsey           #+#    #+#             */
/*   Updated: 2024/03/25 18:23:59 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// go through the input and save each part with a token in lexeme_list
void	add_tokens(t_list_lexeme *list, t_lexer *lexer)
{
	while (peekcharacter(lexer))
	{
		if (is_whitespace(peekcharacter(lexer)))
			getcharacter(lexer);
		else if (is_identifier(peekcharacter(lexer)))
			identifier(list, lexer);
		else if (is_less(peekcharacter(lexer)))
			add_to_lex(list, create_lexeme(LESS, getcharacter(lexer), 1));
		else if (is_greater(peekcharacter(lexer)))
			add_to_lex(list, create_lexeme(GREATER, getcharacter(lexer), 1));
		else if (is_dash(peekcharacter(lexer)))
			add_to_lex(list, create_lexeme(DASH, getcharacter(lexer), 1));
		else if (is_pipes(peekcharacter(lexer)))
			add_to_lex(list, create_lexeme(PIPES, getcharacter(lexer), 1));
		else if (is_expansion(peekcharacter(lexer)))
			add_to_lex(list, create_lexeme(EXPANSION, getcharacter(lexer), 1));
		else if (is_double_quotes(peekcharacter(lexer)))
			add_to_lex(list, create_lexeme(D_QUOTES, getcharacter(lexer), 1));
		else if (is_single_quotes(peekcharacter(lexer)))
			add_to_lex(list, create_lexeme(S_QUOTES, getcharacter(lexer), 1));
		else
			add_to_lex(list, create_lexeme(UNEXPECTED, getcharacter(lexer), 1));
	}
	add_to_lex(list, create_lexeme(END_OF_FILE, "\0", 1));
}

// // go through the input and save each part with a token in lexeme_list
// void	lex(t_list_lexeme *list, t_lexer *lexer)
// {
// 	char	c;
// 	char	u;

// 	while (peekcharacter(lexer))
// 	{
// 		if (is_whitespace(peekcharacter(lexer)))
// 		{
// 			getcharacter(lexer);
// 			continue;
// 		}
// 		else if (is_identifier(peekcharacter(lexer)))
// 			identifier(list, lexer);
// 		else if (is_less(peekcharacter(lexer)))
// 		{
// 			getcharacter(lexer);
// 			add_to_lex(list, create_lexeme(LESS, "<", 1));
// 		}
// 		else if (is_greater(peekcharacter(lexer)))
// 		{
// 			getcharacter(lexer);
// 			add_to_lex(list, create_lexeme(GREATER, ">", 1));
// 		}
// 		else if (is_dash(peekcharacter(lexer)))
// 		{
// 			getcharacter(lexer);
// 			add_to_lex(list, create_lexeme(DASH, "-", 1));
// 		}
// 		else if (is_pipes(peekcharacter(lexer)))
// 		{
// 			getcharacter(lexer);
// 			add_to_lex(list, create_lexeme(PIPES, "|", 1));
// 		}
// 		else if (is_expansion(peekcharacter(lexer)))
// 		{
// 			getcharacter(lexer);
// 			add_to_lex(list, create_lexeme(EXPANSION, "$", 1));
// 		}
// 		else if (is_double_quotes(peekcharacter(lexer)))
// 		{
// 			getcharacter(lexer);
// 			add_to_lex(list, create_lexeme(D_QUOTES, "\"", 1));
// 		}
// 		else if (is_single_quotes(peekcharacter(lexer)))
// 		{
// 			getcharacter(lexer);
// 			add_to_lex(list, create_lexeme(S_QUOTES, "'", 1));
// 		}
// 		else
// 		{
// 			u = getcharacter(lexer);
// 			add_to_lex(list, create_lexeme(UNEXPECTED, &u, 1));
// 		}
// 	}
// 	add_to_lex(list, create_lexeme(END_OF_FILE, &c, 1));
// }
