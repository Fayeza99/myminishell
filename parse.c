/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:11:29 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/02 15:20:16 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cmd(t_cmd *cmd)
{
	printf("parsing cmd...\n");
	// printf("%s\n", cmd->command);
	// turn command to argv
	cmd->argv = get_argv_arr(cmd->command);
	if (!cmd->argv)
		return ;
	// get argv types
	cmd->type = get_type_arr(cmd->argv);
}

// before: mini has full input string
// after: all fields filled, fd on default, argv and types ready
t_mini	*parse_input(t_mini *mini)
{
	t_list	*lst;

	get_commands(mini);
	mini->current_cmd = create_cmdlst(mini->cmd_list);
	lst = mini->current_cmd;
	while (lst)
	{
		parse_cmd((t_cmd *)lst->content);
		lst = lst->next;
	}
	return (mini);
}

int	is_whitespace(char c)
{
	return ((c >= 9 && c < 14) || c == 32);
}

// count pipes outside quotes
int	count_pipes(char *cmd)
{
	int	pipes;
	int	i;

	pipes = 0;
	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '|' && !inside_quote(cmd, i))
		{
			while (cmd[i] && is_whitespace(cmd[i]))
				i++;
			if (cmd[i])
				pipes++;
		}
		i++;
	}
	return (pipes);
}

// saves command list in mini
void	get_commands(t_mini *mini)
{
	int		pipes;
	int		arg;
	char	*last_cmd;
	int		i;

	printf("getting cmd...\n");
	pipes = count_pipes(mini->command);
	mini->cmd_list = (char **)malloc(sizeof(char *) * (pipes + 2));
	if (!mini->cmd_list)
		return ;
	arg = 0;
	last_cmd = mini->command;
	while (arg < pipes + 1)
	{
		i = 0;
		while (last_cmd[i] && is_whitespace(last_cmd[i]))
			i++;
		mini->cmd_list[arg++] = &last_cmd[i];
		while (last_cmd[i] && !(last_cmd[i] == '|' && inside_quote(last_cmd, i) == 0))
			i++;
		last_cmd[i++] = '\0';
		last_cmd += i;
	}
	mini->cmd_list[arg] = NULL;
}
