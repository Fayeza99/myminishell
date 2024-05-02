/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:02:43 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/02 12:07:04 by fnikzad          ###   ########.fr       */
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
					ft_strchr(shell->env[i], '=') - shell->env[i]) == 0)
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
		i = 0;
		j++;
	}
	return (0);
}
