/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:13:02 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/20 12:02:22 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token(char c)
{
	return (c == '\'' || c == '\"' || c == '>' || c == '<' || c == '|');
}

char	get_error_redir(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] && !((str[i] == '>' || str[i] == '<') && !inside_quote(str, i)))
		i++;
	i++;
	if (str[i] == str[i - 1])
		i++;
	else if ((str[i] == '>' || str[i] == '<') && str[i] != str[i - 1])
		return (str[i]);
	while (str[i] && is_whitespace(str[i]))
		i++;
	if (!str[i])
		return ('\n');
	if (((str[i] == '\'' || str[i] == '\"') && str[i] == str[i + 1]) 
		|| is_token(str[i]))
		return (str[i]);
	return ('\n');
}

char	get_error_pipe(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] && !(str[i] == '|' && !inside_quote(str, i)))
		i++;
	while (str[i] && is_whitespace(str[i]))
		i++;
	if (str[i] == '|')
		return ('|');
	return ('\n');
}

// flag: 1 is s_quote, 2 is d_quote, 4 is pipe, 8 is d_pipe, 16 is redir
int	ft_error(int flag, char *str)
{
	char	c;

	c = '\0';
	if (flag & REDIR)
		c = get_error_redir(str);
	if (flag & DPIPE)
		c = get_error_pipe(str);
	ft_putstr_fd("minishell: syntax error near unexpected token \'", 2);
	if (c == '\n')
		ft_putstr_fd("newline", 2);
	else
		ft_putchar_fd(c, 2);
	ft_putstr_fd("\'\n", 2);
	return (0);
}

// // 0--ok 1--reprompt 2--error
// int	check_pipe(char *str)
// {
// 	if (!str || !*str)
// 		return (1);
// 	str++;
// 	while (*str && is_whitespace(*str))
// 		str++;
// 	if (!*str)
// 		return (1);
// 	if (*str == '|')
// 		return (2);
// 	return (0);
// }

// int	is_token(char c)
// {
// 	return (c == '|' || c == '>' || c == '<' || c == '\'' || c == '\"');
// }

// int	valid_input(char *str)
// {
// 	int	flags;

// 	flags = 0;
// 	if (!str || !*str)
// 		return (0);
// 	while (*str)
// 	{
// 		if (!is_token(*str) || )
// 		if (*str == '\'' && !(flags & D_QUOTE))
// 			flags ^= S_QUOTE;
// 		else if (*str == '\"' && !(flags & S_QUOTE))
// 			flags ^= D_QUOTE;
// 		else if (!(flags & D_QUOTE || flags & S_QUOTE)
// 			&& (*str == '|' && check_pipe(str) == 2))
// 			return (flags | ERR);
// 		else if (!(flags & D_QUOTE || flags & S_QUOTE) && *str == '|')
// 			flags |= PIPE;
// 		else if (!is_whitespace(*str) && )
// 		str++;
// 	}
// 	return (flags);
// }
