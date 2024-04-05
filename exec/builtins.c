/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:12:09 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/05 16:15:10 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	ex_pwd(char **args)
// {
// 	char	cwd[1024];
	
// 	if (ft_strncmp(args[0], "pwd", 3) == 0)
// 	{
// 		if (getcwd(cwd, sizeof(cwd)) != 0)
// 			printf("%s\n", cwd);
// 		else
// 			perror("failed");
// 	}
// 	return (0);
// }

int	ex_echo(t_mini *shell)
{
	int	i;
	t_cmd	*cmd;
	cmd = (t_cmd *) shell->current_cmd->content;
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
	{
		if (cmd->argv[1] && cmd->argv[2] && ft_strcmp(cmd->argv[1], "-n") == 0)
			i = 2;
		else
			i = 1;
		while (cmd->argv[i])
		{
			printf("%s", cmd->argv[i++]);
			if (cmd->argv[i])
				printf(" ");
		}
	}
	if (cmd->argv[1] && ft_strcmp(cmd->argv[1], "-n") != 0)
		printf("\n");
	return (0);
}