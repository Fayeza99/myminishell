/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:12:09 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/22 12:57:46 by fnikzad          ###   ########.fr       */
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



int	check_newline1(char *s)
{
	int i = 0;
	if (s[0] == '-')
		i++;
	else
		return (0);
	while (s[i])
	{
		if (s[i] == 'n')
			i++;
		else
			return (0);
	}
	return (i);
}


int	check_newline(char **s)
{
	int i = 0;
	int j = 1;

	while (check_newline1(s[j]))
	{
		i = 0;
		if (s[j][0] == '-')
			i++;
		while (s[j][i])
		{
			if (s[j][i] == 'n')
				i++;
			else
				return (0);
		}
		j++;
	}
	return (j);
}

int	ex_echo(t_mini *shell, t_cmd *cmd)
{
	(void) shell;
	int	i;
	// t_cmd	*cmd;
	int j = 0;
	// cmd = (t_cmd *) shell->current_cmd->content;
	// int k = echo_helper(cmd->argv);
	int k = check_newline(cmd->argv);
	i = 0;
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
	{
		if (check_newline1(cmd->argv[1]))
			j = 1;
		if (cmd->argv[1] && cmd->argv[k] && (check_newline(cmd->argv) != 0))
		{
			i = k;
		}
		else if (cmd->argv[1] && !cmd->argv[k] && (check_newline(cmd->argv) != 0))
			return (0);
		else
			i = 1;
		while (cmd->argv[i])
		{
			// printf("%s", cmd->argv[i++]);
			ft_putstr_fd(cmd->argv[i], cmd->fd_out);
			if (cmd->argv[i + 1])
				ft_putstr_fd(" ", cmd->fd_out);
			i++;
		}
	}
	if (j == 0)
		ft_putstr_fd("\n", cmd->fd_out);
		
	return (0);
}
