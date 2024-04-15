/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:33:50 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/15 13:49:53 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*create_cmdlst(char **s)
{
	t_list	*lst;
	char	*str;
	int		i;

	i = 0;
	while (s && s[i])
	{
		str = s[i] + ft_strlen(s[i]) - 1;
		while (is_whitespace(*str))
			str--;
		str++;
		*str = '\0';
		if (!i)
			lst = ft_lstnew((void *)new_cmd(s[i++]));
		else
			ft_lstadd_back(&lst, ft_lstnew((void *)new_cmd(s[i++])));
	}
	return (lst);
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
	mini->cmd_arr = NULL;
	mini->command = NULL;
	mini->current_cmd = NULL;
	mini->exit_status = 0;
	return (mini);
}
