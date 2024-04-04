/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:59:10 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/04 10:25:39 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

// 0 - ok | 1 - incomplete(prompt again) | 2 - empty pipe(error)
int	open_pipe(char *str)
{
	int	open;
	int	i;

	open = 0;
	i = 0;
	while (str && str[i] && is_whitespace(str[i]))
		i++;
	if (str[i] && str[i] == '|')
		return (2);
	while (str && str[i])
	{
		if (open && str[i] == '|' && !inside_quote(str, i))
			return (2);
		else if (open && !is_whitespace(str[i]) && !inside_quote(str, i))
			open = 0;
		else if (str[i] == '|' && !inside_quote(str, i))
			open = 1;
		i++;
	}
	return (open);
}

// like open_quotes but at position of string
int	inside_quote(char *str, int pos)
{
	int	d_quote;
	int	s_quote;
	int	i;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	while (str && str[i] && i < pos)
	{
		if (str[i] == '\"' && d_quote)
			d_quote = 0;
		else if (str[i] == '\"' && !d_quote && !s_quote)
			d_quote = 1;
		else if (str[i] == '\'' && s_quote)
			s_quote = 0;
		else if (str[i] == '\'' && !s_quote && !d_quote)
			s_quote = 1;
		i++;
	}
	if (s_quote)
		return (1);
	if (d_quote)
		return (2);
	return (0);
}
