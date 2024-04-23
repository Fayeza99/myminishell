/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:33:50 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/23 10:44:19 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
