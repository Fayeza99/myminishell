/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:17:15 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/14 17:17:18 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		built_ins(t_mini *shell)
{
	t_cmd *cmd;
	cmd = (t_cmd *) shell->current_cmd->content;
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
	{
		ex_cd(cmd->argv, shell);
		return (1);
	}
	if (ft_strcmp(cmd->argv[0], "export") == 0)
	{
		ex_export(shell, cmd->argv);
		return (1);
	}
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
	{
		ex_echo(shell);
		return(1);
	}
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
	{
		ex_pwd(cmd->argv);
		return (1);
	}
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
	{
		ex_unset(shell);
		return (1);
	}
	return (0);
}


void	exec_pipes(t_mini *shell)
{
	t_cmd	*cmd;
	int		fd[2];
	int		pid;
	int		pid2 = -1;
	
	if (built_ins(shell) != 0)
		return ;
	while (shell->current_cmd)
	{
		cmd = shell->current_cmd->content;
		
		pipe (fd);
		pid = fork();
		if (!pid)
		{
			if (pid2 != -1)
			{
				dup2(pid2, 0);
				close(pid2);
			}
			if (shell->current_cmd->next)
			{
				dup2(fd[1], 1);
			}
			close(fd[0]);
			execve(find_path(cmd->argv[0]), cmd->argv, shell->env);
			exit(1);
		}
		else
		{
			if (pid2 != -1)
			{
				close (pid2);
			}
			pid2 = fd[0];
			close(fd[1]);
			waitpid(pid, NULL, 0);
			shell->current_cmd = shell->current_cmd->next;
		}
		
	}
}