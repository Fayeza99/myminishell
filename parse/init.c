/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:33:50 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/04 13:52:18 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*create_cmdlst(char **s)
{
	t_list	*lst;
	char	*str;
	int		i;

	i = 0;
	if (s && s[0])
	{
		str = s[0] + ft_strlen(s[0]) - 1;
		while (is_whitespace(*str))
			str--;
		str++;
		*str = '\0';
		lst = ft_lstnew((void *)new_cmd(s[i++]));
	}
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

void	*ft_delcmd(void *cmd)
{
	t_cmd	*c;

	c = (t_cmd *)cmd;
	// ft_freearr(c->argv);
	free(c);
	return (NULL);
}

int	mini_free(t_mini *mini)
{
	int	exit;

	exit = mini->exit_status;
	free(mini->command);
	free(mini->cmd_list);
	ft_freearr(mini->env);
	ft_lstclear(&mini->current_cmd, ft_delcmd(&mini->current_cmd));
	free(mini);
	return (exit);
}

t_mini	*mini_init(char **env)
{
	t_mini	*mini;

	mini = (t_mini *)malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->cmd_list = NULL;
	mini->command = NULL;
	mini->current_cmd = NULL;
	mini->env = ft_arrdup(env);
	mini->exit_status = 0;
	return (mini);
}
