/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:11:41 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/15 15:54:02 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_delcmd(void *cmd)
{
	t_cmd	*c;

	c = (t_cmd *)cmd;
	ft_freearr(c->argv);
	free(c);
	return (NULL);
}

int	mini_free(t_mini *mini)
{
	int		exit;
	t_list	*lst;

	exit = mini->exit_status;
	free(mini->command);
	free(mini->cmd_arr);
	while (mini->current_cmd)
	{
		lst = mini->current_cmd;
		ft_delcmd(lst->content);
		mini->current_cmd = mini->current_cmd->next;
		free(lst);
	}
	ft_freearr(mini->env);
	free(mini);
	return (exit);
}

int	micro_free(t_mini *mini)
{
	int		exit;
	t_list	*lst;

	exit = mini->exit_status;
	free(mini->command);
	free(mini->cmd_arr);
	while (mini->current_cmd)
	{
		lst = mini->current_cmd;
		ft_delcmd(lst->content);
		mini->current_cmd = mini->current_cmd->next;
		free(lst);
	}
	return (exit);
}
