/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:06:25 by asemsey           #+#    #+#             */
/*   Updated: 2024/05/01 15:15:12 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cmdprint(t_list *lst)
{
	t_cmd	*cont;

	while (lst)
	{
		cont = (t_cmd *)lst->content;
		printf("cmd---%s\n", cont->command);
		lst = lst->next;
	}
}

void	print_arr(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		printf("%s\n", s[i++]);
}

// void	print_types(t_type *type, int len)
// {
// 	int	i;

// 	i = 0;
// 	while (type && i < len)
// 		printf(" %d ", type[i++]);
// 	printf("\n");
// }

void	display_struct(t_mini *mini)
{
	t_list	*lst;
	t_cmd	*cmd;

	printf("\n--displaying struct--\n");
	lst = mini->current_cmd;
	while (lst)
	{
		cmd = (t_cmd *)lst->content;
		printf("next command: fd_in %d, fd_out %d\n", cmd->fd_in, cmd->fd_out);
		printf("args:\n");
		print_arr(cmd->argv);
		printf("\n");
		lst = lst->next;
	}
}
