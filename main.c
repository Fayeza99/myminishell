/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:01 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/27 19:37:06 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "tokens/lexer.h"

// void	get_args(t_mini *mini, char *cmd)
// {
// 	mini->current_cmd->
// }

void	print_command(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
		printf("%s\n", cmd[i++]);
}

int	read_command(t_mini *mini)
{
	mini->command = readline("minishell> ");
	add_history(mini->command);
	get_commands(mini);
	print_command(mini->cmd_list);
	return (1);
}

t_mini	*mini_init(char **env)
{
	t_mini	*mini;

	mini = (t_mini *)malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->cmd_count = 0;
	mini->cmd_list = NULL;
	mini->command = NULL;
	mini->current_cmd = NULL;
	mini->env = env; // arrdup(env)
	mini->exit_status = 0;
	return (mini);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;
	int		exit;

	(void)argc;
	(void)argv;
	mini = mini_init(env);
	if (!mini)
		return (EXIT_FAILURE);
	while (1)
	{
		if (!read_command(mini))
			break ;
	}
	exit = mini->exit_status;
	// free_mini(mini);
	return (exit);
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
