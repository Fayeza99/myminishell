/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:55:42 by asemsey           #+#    #+#             */
/*   Updated: 2024/03/26 16:48:27 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	ft_tokens1(t_list_lexeme *list, t_lexer *lexer)
{
	char	c;

	if (is_whitespace(peekcharacter(lexer)))
	{
		getcharacter(lexer);
		return (1);
	}
	else if (is_identifier(peekcharacter(lexer)))
		return (identifier(list, lexer));
	else if (is_less(peekcharacter(lexer)))
	{
		c = getcharacter(lexer);
		return (add_to_lex(list, create_lexeme(LESS, &c, 1)));
	}
	else if (is_greater(peekcharacter(lexer)))
	{
		c = getcharacter(lexer);
		return (add_to_lex(list, create_lexeme(GREATER, &c, 1)));
	}
	else if (is_dash(peekcharacter(lexer)))
	{
		c = getcharacter(lexer);
		return (add_to_lex(list, create_lexeme(DASH, &c, 1)));
	}
	return (0);
}

static void	ft_tokens2(t_list_lexeme *list, t_lexer *lexer)
{
	char	c;

	if (is_pipes(peekcharacter(lexer)))
	{
		c = getcharacter(lexer);
		add_to_lex(list, create_lexeme(PIPES, &c, 1));
	}
	else if (is_expansion(peekcharacter(lexer)))
	{
		c = getcharacter(lexer);
		add_to_lex(list, create_lexeme(EXPANSION, &c, 1));
	}
	else if (is_double_quotes(peekcharacter(lexer)))
		quoted_str(list, lexer);
	else if (is_single_quotes(peekcharacter(lexer)))
		s_quoted_str(list, lexer);
	else
	{
		c = getcharacter(lexer);
		add_to_lex(list, create_lexeme(UNEXPECTED, &c, 1));
	}
}

// go through the input and save each part with a token in lexeme_list
void	add_tokens(t_list_lexeme *list, t_lexer *lexer)
{
	while (peekcharacter(lexer))
	{
		if (!ft_tokens1(list, lexer))
			ft_tokens2(list, lexer);
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
