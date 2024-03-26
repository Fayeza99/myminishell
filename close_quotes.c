/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:59:10 by asemsey           #+#    #+#             */
/*   Updated: 2024/03/26 17:27:16 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 0 - none | 1 - s_quote open | 2 - d_quote open
int	open_quotes(char *str)
{
	int	d_quote;
	int	s_quote;

	s_quote = 0;
	d_quote = 0;
	while (str && *str)
	{
		if (*str == '\"' && d_quote)
			d_quote = 0;
		else if (*str == '\"' && !d_quote && !s_quote)
			d_quote = 1;
		else if (*str == '\'' && s_quote)
			s_quote = 0;
		else if (*str == '\'' && !s_quote && !d_quote)
			s_quote = 1;
		str++;
	}
	if (s_quote)
		return (1);
	if (d_quote)
		return (2);
	return (0);
}
