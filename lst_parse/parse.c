/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:11:29 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/24 11:28:44 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_cmd(t_mini *mini, t_cmd *cmd);
void	get_commands(t_mini *mini);
void	nullterminate_cmd(t_list *lst);
int		count_pipes(char *cmd);

// before: mini has full input string
// after: all fields filled, fd on open files, argv ready
void	parse_input(t_mini *mini)
{
	t_list	*lst;

	get_commands(mini);
	nullterminate_cmd(mini->current_cmd);
	lst = mini->current_cmd;
	while (lst)
	{
		parse_cmd(mini, (t_cmd *)lst->content);
		if (mini->exit_status)
			return ;
		lst = lst->next;
	}
}

void	parse_cmd(t_mini *mini, t_cmd *cmd)
{
	cmd->args = get_argv_lst(cmd->command);
	if (!cmd->args)
		return ;
	split_argv(cmd->args);
	cmd->type = get_type_arr(cmd->args);
	unquote_argv(&cmd->args);
	set_cmd_fd(mini, cmd);
	cmd->argv = ft_lst_toarr(cmd->args);
	ft_lst_delall(&cmd->args, NULL);
	free(cmd->type);
}

void	nullterminate_cmd(t_list *lst)
{
	t_cmd	*cmd;
	char	*str;

	while (lst)
	{
		cmd = (t_cmd *)lst->content;
		str = cmd->command + ft_strlen(cmd->command) - 1;
		while (is_whitespace(*str))
			str--;
		str++;
		*str = '\0';
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

// saves command list in mini, works for sure
void	get_commands(t_mini *mini)
{
	char	*last_cmd;
	int		i;
	int		count;
	int		c;

	count = count_pipes(mini->command);
	last_cmd = mini->command;
	c = 0;
	while (c <= count)
	{
		i = 0;
		while (last_cmd[i] && is_whitespace(last_cmd[i]))
			i++;
		if (mini->current_cmd)
			ft_lstadd_back(&mini->current_cmd, \
			ft_lstnew(new_cmd(&last_cmd[i])));
		else
			mini->current_cmd = ft_lstnew(new_cmd(&last_cmd[i]));
		while (last_cmd[i] && !(last_cmd[i] == '|'
				&& inside_quote(last_cmd, i) == 0))
			i++;
		last_cmd[i++] = '\0';
		last_cmd += i;
		c++;
	}
}
