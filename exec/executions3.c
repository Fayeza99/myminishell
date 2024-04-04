/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:06:55 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/04 13:23:02 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipes2(t_mini *shell)
{
	t_list	*lst;
	int		fd[2];
	int		pid;
	int		pid2;

	pipe(fd);
	lst = shell->current_cmd;
	while (lst)
	{
		if (!lst->next)
		{
			pid = fork();
			if (!pid)
			{
				
			}
		}
		else
		{
			pid2 = fork();
			if (!pid2)
			{
				
			}
		}
		lst = lst->next;
	}
}