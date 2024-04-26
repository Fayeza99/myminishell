/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:31:29 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/26 12:13:20 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reprompt(char **str, int flag)
{
	char	*line;

	g_sig |= INTERACT;
	if (flag & S_QUOTE)
		ft_putstr_fd("quote", STDERR_FILENO);
	else if (flag & D_QUOTE)
		ft_putstr_fd("dquote", STDERR_FILENO);
	else if (flag & PIPE)
		ft_putstr_fd("pipe", STDERR_FILENO);
	line = readline("> ");
	if (!line)
	{
		g_sig ^= INTERACT;
		return ;
	}
	*str = ft_freejoin(*str, "\n");
	*str = ft_freejoin(*str, line);
	free(line);
	g_sig ^= INTERACT;
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
	if (mini->command == NULL)
	{
		ft_putendl_fd("--NULL--", 2);
		return (0);
	}
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
