/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:01 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/02 14:18:55 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leak(void);


int	read_command(t_mini *mini)
{
	t_cmd	*cmd;
	if (mini->command)
		free(mini->command);
	mini->command = readline("minishell> ");
	if (open_pipe(mini->command) == 2 || !*mini->command)
		return (1);
	while (open_quotes(mini->command) || open_pipe(mini->command) == 1)
	{
		mini->command = ft_freejoin(mini->command,\
			ft_freejoin(ft_strdup("\n"), readline("> ")));
		if (open_pipe(mini->command) == 2)
			return (1);
	}
	add_history(mini->command);
	if (!ft_strncmp(mini->command, "exit", ft_strlen(mini->command)))
		return (0);
	get_commands(mini);
	mini->current_cmd = create_cmdlst(mini->cmd_list);
	cmd = (t_cmd *)mini->current_cmd->content;
	// cmd->argv = get_argv(cmd->command);
	return (1);
}

void	leak(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;

	(void)argc;
	(void)argv;
	atexit(leak);
	mini = mini_init(env); 
	if (!mini)
		return (EXIT_FAILURE);
	while (1)
	{
		if (!read_command(mini))
			break ;
	exec_cmd(mini);
		// leak();
	}
	return (mini_free(mini));
}

