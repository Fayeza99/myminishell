/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:01 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/05 20:23:32 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leak(void);

int	read_command(t_mini *mini)
{
	char	*tmp;
	char	*endl;

    mini->command = readline("minishell> ");
    if (open_pipe(mini->command) == 2 || !*mini->command)
        return (1);
    while (open_quotes(mini->command) || open_pipe(mini->command) == 1)
    {
        tmp = readline("> ");
        endl = ft_freejoin(ft_strdup("\n"), tmp);
        mini->command = ft_freejoin(mini->command, endl);
        free(endl);
        free(tmp);
        if (open_pipe(mini->command) == 2)
            return (1);
    }
    add_history(mini->command);
    mini->command = ft_expand(mini->command, mini->env);
    parse_input(mini);
    if (!ft_strcmp(mini->command, "exit"))
        return (0);
    // display_struct(mini);
    return (1);
}

void	leak(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;

	// atexit(leak);
	(void)argc;
	(void)argv;
	mini = mini_init();
	if (!mini)
		return (EXIT_FAILURE);
	mini->env = ft_arrdup(env);
	while (1)
	{
		if (!read_command(mini))
			break ;
		pipes(mini);
		// exec_cmd(mini);
		micro_free(mini);
		// leak();
	}
	mini_free(mini);
	rl_clear_history();
	return (1);
}
