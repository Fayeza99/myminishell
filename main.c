/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:01 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/04 22:42:47 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// problem: empty arg before pipe

void	leak(void);

void	display_struct(t_mini *mini)
{
	t_list	*lst;
	t_cmd	*cmd;

	printf("\n--displaying struct--\n");
	lst = mini->current_cmd;
	while (lst)
	{
		cmd = (t_cmd *)lst->content;
		printf("next command:   %s\n", cmd->command);
		printf("args:\n");
		print_argv(cmd->argv, cmd->type);
		lst = lst->next;
	}
}

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
		endl = ft_strdup("\n");
		mini->command = ft_freejoin(mini->command,\
			ft_strjoin(endl, tmp));
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

	atexit(leak);
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
		// pipes(mini);
		// exec_cmd(mini);
		micro_free(mini);
		// leak();
	}
	mini_free(mini);
	rl_clear_history();
	return (1);
}
