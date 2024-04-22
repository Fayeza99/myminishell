/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:01 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/20 12:28:46 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leak(void)
{
	system("leaks minishell");
}

// int	read_command(t_mini *mini)
// {
// 	char	*tmp;
// 	char	*endl;

// 	mini->command = readline("minishell> ");
// 	if (!mini->command)
// 		return (0);
// 	if (!*mini->command || open_pipe(mini->command) == 2)
// 		return (free(mini->command), 2);
// 	while (open_quotes(mini->command) || open_pipe(mini->command) == 1)
// 	{
// 		tmp = readline("> ");
// 		endl = ft_freejoin(ft_strdup("\n"), tmp);
// 		mini->command = ft_freejoin(mini->command, endl);
// 		free(endl);
// 		free(tmp);
// 		if (open_pipe(mini->command) == 2)
// 			return (free(mini->command), 2);
// 	}
// 	add_history(mini->command);
// 	mini->command = ft_expand(mini, mini->command);
// 	parse_input(mini);
// 	// if (!ft_strcmp(mini->command, "exit"))
// 	// 	return (0);
// 	// display_struct(mini);
// 	return (1);
// }

int	main(int argc, char **argv, char **env)
{
	t_mini				*mini;
	int					status;

	(void)argc;
	(void)argv;
	mini = mini_init();
	if (!mini)
		return (EXIT_FAILURE);
	mini->env = ft_arrdup(env);
	while (1)
	{
		status = read_command(mini);
		if (!status)
			break ;
		if (status == 2)
			continue ;
		// pipes(mini);
		m_exec(mini);
		// exec_cmd(mini);
		// printf("hello\n");
		micro_free(mini);
		// leak();
	}
	rl_clear_history();
	// mini_free(mini);
	return (mini_free(mini));
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_mini				*mini;
// 	struct sigaction	sa;
// 	int					status;
// 	// struct termios		original_termios;

// 	// atexit(leak);
// 	sa.sa_sigaction = mini_handler;
// 	sa.sa_flags = 0;
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// 	sigaction(SIGTERM, &sa, NULL);
// 	// enable_raw_mode(&original_termios);
// 	(void)argc;
// 	(void)argv;
// 	mini = mini_init();
// 	if (!mini)
// 		return (EXIT_FAILURE);
// 	mini->env = ft_arrdup(env);
// 	while (1)
// 	{
// 		status = read_command(mini);
// 		if (!status)
// 			break ;
// 		if (status == 2)
// 			continue ;
// 		// pipes(mini);
// 		// exec_cmd(mini);
// 		micro_free(mini);
// 		// leak();
// 	}
// 	mini_free(mini);
// 	rl_clear_history();
// 	// disable_raw_mode(&original_termios);
// 	return (1);
// }
