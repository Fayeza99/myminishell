/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:33:50 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/05 14:12:25 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*create_cmdlst(char **s)
{
	t_list	*lst;
	char	*str;
	int		i;

	if (s && s[0])
	{
		str = s[0] + ft_strlen(s[0]) - 1;
		while (is_whitespace(*str))
			str--;
		str++;
		*str = '\0';
		lst = ft_lstnew((void *)new_cmd(s[0]));
	}
	i = 1;
	while (s && s[i])
	{
		str = s[i] + ft_strlen(s[i]) - 1;
		while (is_whitespace(*str))
			str--;
		str++;
		*str = '\0';
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
