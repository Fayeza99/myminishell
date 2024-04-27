/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:02:43 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/27 16:07:44 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ex_unset(t_mini *shell, t_cmd *cmd)
{
	int	i;
	int	j = 1;
	// t_cmd	*cmd;

	// cmd = shell->current_cmd->content;
	while (cmd->argv[j])
	{
		i = 0;
		while (shell->env[i])
		{
			if (ft_strncmp(shell->env[i], cmd->argv[j], ft_strchr(shell->env[i], '=') - shell->env[i]) == 0)
			{
				while (shell->env[i])
				{
					// printf("%s\n", shell->env[i]);
					shell->env[i] = shell->env[i + 1];
					i++;
				}
				// shell->exit_status = 0;
			}
			else
				i++;
		}
		// if (i == ft_arrlen(shell->env))
			
		i = 0;
		j++;
	}
	return (0);
}
