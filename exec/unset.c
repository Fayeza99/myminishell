/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:02:43 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/02 14:13:33 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ex_unset(t_mini *shell, t_cmd *cmd)
{
	int	i;
	int	j;

	j = 1;
	while (cmd->argv[j])
	{
		i = 0;
		while (shell->env[i])
		{
			if (ft_strncmp(shell->env[i], cmd->argv[j],
					ft_strlen(cmd->argv[j])) == 0)
			{
				free (shell->env[i]);
				while (shell->env[i])
				{
					shell->env[i] = shell->env[i + 1];
					i++;
				}
			}
			else
				i++;
		}
		j++;
	}
	return (0);
}
