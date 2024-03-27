/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:42:12 by asemsey           #+#    #+#             */
/*   Updated: 2024/03/26 16:56:48 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer.h"

void	quoted_str(t_list_lexeme *list, t_lexer *lexer)
{
	char	buffer[1000];
	int		i;

	i = 0;
	getcharacter(lexer);
	while ((is_identifier(peekcharacter(lexer)) || is_dash(peekcharacter(lexer))
			|| is_less(peekcharacter(lexer)) || is_greater(peekcharacter(lexer))
			|| is_expansion(peekcharacter(lexer))
			|| is_whitespace(peekcharacter(lexer))
			|| is_single_quotes(peekcharacter(lexer))
			|| is_pipes(peekcharacter(lexer)))
		&& !(is_double_quotes(peekcharacter(lexer))))
	{
		buffer[i] = (char)getcharacter(lexer);
		i++;
	}
	buffer[i] = '\0';
	if (is_double_quotes(peekcharacter(lexer)))
		getcharacter(lexer);
	add_to_lex(list, create_lexeme(D_QUOTES, buffer, i));
}

void	s_quoted_str(t_list_lexeme *list, t_lexer *lexer)
{
	char	buffer[1000];
	int		i;

	i = 0;
	getcharacter(lexer);
	while ((is_identifier(peekcharacter(lexer)) || is_dash(peekcharacter(lexer))
			|| is_less(peekcharacter(lexer)) || is_greater(peekcharacter(lexer))
			|| is_expansion(peekcharacter(lexer))
			|| is_whitespace(peekcharacter(lexer))
			|| is_double_quotes(peekcharacter(lexer))
			|| is_pipes(peekcharacter(lexer)))
		&& !(is_single_quotes(peekcharacter(lexer))))
	{
		buffer[i] = (char)getcharacter(lexer);
		i++;
	}
	buffer[i] = '\0';
	if (is_single_quotes(peekcharacter(lexer)))
		getcharacter(lexer);
	add_to_lex(list, create_lexeme(S_QUOTES, buffer, i));
}
