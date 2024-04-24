/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:33:50 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/24 11:23:20 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*new_cmd(char *command)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->command = command;
	new->argv = NULL;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	return (new);
}

t_mini	*mini_init(void)
{
	t_mini	*mini;

	mini = (t_mini *)malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->command = NULL;
	mini->current_cmd = NULL;
	mini->exit_status = 0;
	return (mini);
}
