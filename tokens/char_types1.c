/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_types1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:50:53 by asemsey           #+#    #+#             */
/*   Updated: 2024/03/25 18:11:27 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		is_whitespace(char c)
{
	return ((c >= 9 && c < 14) || c == 32);
}

int		is_identifier(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int		is_double_quotes(char c)
{
	return (c == '"');
}

int		is_single_quotes(char c)
{
	return (c == '\'');
}

int		is_expansion(char c)
{
	return (c == '$');
}
