/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:01 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/30 13:13:40 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (mini->command && *mini->command)
			m_exec(mini);
		if (status)
			micro_free(mini);
	}
	rl_clear_history();
	return (mini_free(mini));
}
