/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:01 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/02 15:56:11 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	parse_input(mini);
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

	(void)argc;
	(void)argv;
	// atexit(leak);
	mini = mini_init(env); 
	if (!mini)
		return (EXIT_FAILURE);
	while (1)
	{
		if (!read_command(mini))
			break ;
		pipes(mini);
		// exec_cmd(mini);
		// leak();
	}
	return (mini_free(mini));
}

