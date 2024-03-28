/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_types2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:54:55 by asemsey           #+#    #+#             */
/*   Updated: 2024/03/26 16:49:25 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_less(char c)
{
	return (c == '<');
}

int	is_greater(char c)
{
	return (c == '>');
}

int	is_pipes(char c)
{
	return (c == '|');
}

int	is_dash(char c)
{
	return (c == '-');
}

int	is_eof(char c)
{
	return (c == '\0');
}