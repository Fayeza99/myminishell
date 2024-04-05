/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:02:43 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/05 19:43:36 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ex_unset(t_mini *shell)
{
	int i = -1;
	int j = 1;
	t_cmd	*cmd;

	cmd = shell->current_cmd->content;
	while (cmd->argv[j])
	{
		i = -1;
		while (shell->env[++i])
		{
// dprintf(2,"con1111111111111\n");
// dprintf(2,"con %p\n", shell->env[i]);
// dprintf(2,"con2222222222222\n");
			if (ft_strncmp(shell->env[i], cmd->argv[j], ft_strchr(shell->env[i], '=') - shell->env[i]) == 0)
			{
				while (shell->env[i])
				{
					shell->env[i] = shell->env[i + 1];
					i++;
				}
			}
		}
		j++;
	}
	return (0);
}
