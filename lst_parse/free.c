/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:11:41 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/23 10:14:52 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// to call AFTER successful parsing, only frees argv
void	ft_delcmd(void *cmd)
{
	t_cmd	*c;

	c = (t_cmd *)cmd;
	ft_freearr(c->argv);
	free(c);
}

int	mini_free(t_mini *mini)
{
	int		exit;

	exit = mini->exit_status;
	free(mini->command);
	ft_lst_delall(&mini->current_cmd, ft_delcmd);
	ft_freearr(mini->env);
	free(mini);
	return (exit);
}

int	micro_free(t_mini *mini)
{
	int		exit;

	exit = mini->exit_status;
	free(mini->command);
	ft_lst_delall(&mini->current_cmd, ft_delcmd);
	return (exit);
}
