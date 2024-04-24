/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:31:29 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/24 11:21:21 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reprompt(char **str, int flag)
{
	if (flag & S_QUOTE)
		printf("quote");
	else if (flag & D_QUOTE)
		printf("dquote");
	else if (flag & PIPE)
		printf("pipe");
	*str = ft_freejoin(*str, "\n");
	*str = ft_freejoin(*str, readline("> "));
}

int	check_cmd(char **str)
{
	int	flag;

	while (1)
	{
		flag = get_flag(*str);
		if (flag & DPIPE || flag & REDIR)
			return (ft_error(flag, *str));
		if (flag)
			reprompt(str, flag);
		else
			break ;
	}
	return (1);
}

int	read_command(t_mini *mini)
{
	mini->command = readline("minishell> ");
	if (!mini->command || !*mini->command)
		return (0);
	if (!check_cmd(&mini->command))
	{
		add_history(mini->command);
		return (free(mini->command), 0);
	}
	add_history(mini->command);
	mini->command = ft_expand(mini, mini->command);
	parse_input(mini);
	// display_struct(mini);
	return (1);
}
