/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:11:29 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/05 14:14:24 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_quotes(char **argv)
{
	char	*str;
	int		i;

	i = 0;
	while (argv && argv[i])
	{
		if (*argv[i] == '\'' || *argv[i] == '\"')
		{
			str = ++argv[i];
			while (*str)
				str++;
			*(str - 1) = '\0';
		}
		i++;
	}
}

void	parse_cmd(t_cmd *cmd)
{
	cmd->argv = get_argv_arr(cmd->command);
	if (!cmd->argv)
		return ;
	split_argv(cmd->argv);
	remove_quotes(cmd->argv);
	cmd->type = get_type_arr(cmd->argv);
}

// before: mini has full input string
// after: all fields filled, fd on default, argv and types ready
void	parse_input(t_mini *mini)
{
	t_list	*lst;

	get_commands(mini);
	mini->current_cmd = create_cmdlst(mini->cmd_arr);
	lst = mini->current_cmd;
	while (lst)
	{
		parse_cmd((t_cmd *)lst->content);
		lst = lst->next;
	}
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

	pipes = count_pipes(mini->command);
	mini->cmd_arr = (char **)malloc(sizeof(char *) * (pipes + 2));
	if (!mini->cmd_arr)
		return ;
	arg = 0;
	last_cmd = mini->command;
	while (arg < pipes + 1)
	{
		i = 0;
		while (last_cmd[i] && is_whitespace(last_cmd[i]))
			i++;
		mini->cmd_arr[arg++] = &last_cmd[i];
		while (last_cmd[i] && !(last_cmd[i] == '|'
				&& inside_quote(last_cmd, i) == 0))
			i++;
		last_cmd[i++] = '\0';
		last_cmd += i;
	}
	mini->cmd_arr[arg] = NULL;
}
