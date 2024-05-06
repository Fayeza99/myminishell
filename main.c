/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:01 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/06 12:52:08 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	g_sig = 0;

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;
	int		status;

	(void)argc;
	(void)argv;
	mini = mini_init();
	if (!mini)
		return (EXIT_FAILURE);
	mini->env = ft_arrdup(env);
	sig_init();
	configure_terminal();
	while (1)
	{
		g_sig = 0;
		status = read_command(mini);
		g_sig = 1;
		if (status)
		{
			m_exec(mini);
			micro_free(mini);
		}
	}
	rl_clear_history();
	return (mini_free(mini));
}
