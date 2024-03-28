/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:01 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/28 18:38:08 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leak(void);

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
	get_commands(mini);
	// mini->current_cmd = create_cmdlst(mini->cmd_list);
	// ft_lstprint(mini->current_cmd);
	print_arr(mini->cmd_list);
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
		// leak();
	}
	return (mini_free(mini));
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_list_lexeme	*list;
// 	t_lexer			lexer;
// 	t_list			*node;
// 	t_lexeme		*lexeme;
// 	char			*s;

// 	list = create_list();
// 	while (1)
// 	{
// 		s = readline("minishell> ");
// 		add_history(s);
// 		printf("%d\n", open_quotes(s));
// 		lexer.current = s;
// 		add_tokens(list, &lexer);
// 		node = list->first;
// 		while (node)
// 		{
// 			lexeme = node->content;
// 			if (node->next != NULL)
// 			{
// 				printf("%s - ", get_token_name(lexeme->token));
// 				printf("%s - ", lexeme->str.str);
// 			}
// 			else
// 				printf("%s - %s \n", get_token_name(lexeme->token), lexeme->str.str);
// 			node = node->next;
// 		}
// 		free(s);
// 		delete_list(list);
// 	}
// 	clear_history();
// 	free(list);
// }

