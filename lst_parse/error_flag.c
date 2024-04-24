/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:59:10 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/24 11:20:21 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// check open quotes at position of string
int	inside_quote(char *str, int pos)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (str && str[i] && i < pos)
	{
		if (str[i] == '\'' && !(flag & D_QUOTE))
			flag ^= S_QUOTE;
		else if (str[i] == '\"' && !(flag & S_QUOTE))
			flag ^= D_QUOTE;
		i++;
	}
	return (flag);
}

int	check_redir(char *str)
{
	int	skip;

	skip = 1;
	str++;
	if (*str == '>' || *str == '<')
	{
		if (*str != *(str - 1))
			return (0);
		str++;
		skip = 2;
	}
	while (*str && is_whitespace(*str))
		str++;
	if ((!*str) || ((*str == '\"' || *str == '\'') && *str == *(str + 1))
		|| *str == '|' || *str == '>' || *str == '<')
		return (0);
	return (skip);
}

// checks if all redirecions are valid
int	valid_redir(char *str)
{
	int	redir;
	int	i;

	i = 0;
	while (str && str[i])
	{
		if ((str[i] == '>' || str[i] == '<') && !inside_quote(str, i))
		{
			redir = check_redir(&str[i]);
			if (!redir)
				return (0);
			i += redir;
		}
		else
			i++;
	}
	return (1);
}

// flag: 1 is s_quote, 2 is d_quote, 4 is pipe, 8 is d_pipe, 16 is redir
int	get_flag(char *str)
{
	int		flag;

	flag = 0;
	if (!valid_redir(str))
		return (REDIR);
	while (str && *str && is_whitespace(*str))
		str++;
	if (str && *str && *str == '|')
		return (DPIPE);
	while (str && *str)
	{
		if (*str == '\'' && !(flag & D_QUOTE))
			flag ^= S_QUOTE;
		else if (*str == '\"' && !(flag & S_QUOTE))
			flag ^= D_QUOTE;
		else if ((flag & PIPE) && *str == '|'
			&& !(flag & D_QUOTE || flag & S_QUOTE))
			return (DPIPE);
		else if ((flag & PIPE) && !is_whitespace(*str))
			flag ^= PIPE;
		else if (*str == '|' && !(flag & D_QUOTE || flag & S_QUOTE))
			flag |= PIPE;
		str++;
	}
	return (flag);
}
