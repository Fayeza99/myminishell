/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:33:50 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/04 22:27:29 by asemsey          ###   ########.fr       */
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

void	*ft_delcmd(void *cmd)
{
	t_cmd	*c;

	c = (t_cmd *)cmd;
	free(c->argv);
	free(c->type);
	free(c);
	return (NULL);
}

int	mini_free(t_mini *mini)
{
	int	exit;
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
