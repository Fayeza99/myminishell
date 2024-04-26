/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:17:15 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/26 14:32:57 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int		built_ins(t_mini *shell)
// {
// 	t_cmd *cmd;
// 	cmd = (t_cmd *) shell->current_cmd->content;
// 	if (ft_strcmp(cmd->argv[0], "cd") == 0)
// 	{
// 		ex_cd(cmd->argv, shell);
// 		return (1);
// 	}
// 	if (ft_strcmp(cmd->argv[0], "export") == 0)
// 	{
// 		ex_export(shell, cmd->argv);
// 		return (1);
// 	}
// 	if (ft_strcmp(cmd->argv[0], "echo") == 0)
// 	{
// 		ex_echo(shell);
// 		return(1);
// 	}
// 	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
// 	{
// 		ex_pwd(cmd->argv);
// 		return (1);
// 	}
// 	if (ft_strcmp(cmd->argv[0], "unset") == 0)
// 	{
// 		ex_unset(shell);
// 		return (1);
// 	}
// 	if (ft_strcmp(cmd->argv[0], "exit") == 0)
// 	{
// 		ft_exit(shell);
// 		return (1);
// 	}
// 	return (0);
// }


void		built_ins2(t_mini *shell, t_cmd *cmd)
{
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
	{
		ft_putendl_fd("no such file or directory", 2);
		shell->exit_status = 1;
		exit(shell->exit_status);

		return ;
	}
	
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
	{
		ex_cd(cmd->argv, shell);
	}
	if (ft_strcmp(cmd->argv[0], "export") == 0)
	{
		ex_export(shell, cmd->argv);
	}
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
	{
		ex_echo(shell, cmd);
	}
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
	{
		ex_pwd(cmd->argv);
	}
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
	{
		ex_unset(shell, cmd);
	}
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		ft_exit(shell, cmd);
	}
}
