/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:11:29 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/27 19:34:27 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return ((c >= 9 && c < 14) || c == 32);
}

int	count_pipes(char *cmd)
{
	int	pipes;

	pipes = 0;
	while (cmd && *cmd)
	{
		if (*cmd == '|')
			pipes++;
		cmd++;
	}
	return (pipes);
}

int	get_argc(char *cmd)
{
	int	argc;

	argc = 0;
	while (cmd && *cmd)
	{
		while (is_whitespace(*cmd))
			cmd++;
		if (*cmd)
			argc++;
		while (!is_whitespace(*cmd))
			cmd++;
	}
	return (argc);
}

void	get_commands(t_mini *mini)
{
	int		pipes;
	int		i;
	char	*cmd;

	pipes = count_pipes(mini->command);
	cmd = mini->command;
	mini->cmd_list = (char **)malloc(pipes + 2);
	if (!mini->cmd_list)
		return ;
	i = 0;
	while (i < pipes + 1)
	{
		while (*cmd && is_whitespace(*cmd))
			cmd++;
		mini->cmd_list[i] = cmd;
		while (*cmd && *cmd != '|')
			cmd++;
		*cmd = '\0';
		if (*cmd)
			cmd++;
		i++;
	}
	mini->cmd_list[i] = NULL;
}
