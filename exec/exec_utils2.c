/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:26:30 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/30 12:35:43 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_external(t_mini *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		*fd;

	fd = malloc (sizeof(int) * 2);
	fd[0] = cmd->fd_in;
	fd[1] = cmd->fd_out;
	if (fd[0] == -1 || fd[1] == -1)
	{
		ft_putendl_fd("no such file or directory", 2);
		shell->exit_status = 1;
		return ;
	}
	pid = fork();
	if (!pid)
		child_process(cmd, fd, shell);
	else
		parent_process(pid, shell);
	free (fd);
}

void	redirect_std_io(int **fd, int i, t_mini *shell)
{
	if (i == 0)
	{
		if (dup2(fd[i][1], STDOUT_FILENO) == -1)
			perror("");
	}
	else if (i == count_cmd(shell))
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
	}
	else
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		dup2(fd[i][1], STDOUT_FILENO);
	}
}

void	close_file_descriptors(int **fd, int cmd_count)
{
	int	j;

	j = 0;
	while (j <= cmd_count)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
}

void	handle_fd_redirections(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

void	execute_command(t_mini *shell, t_cmd *cmd)
{
	if (cmd->fd_in == -1 || cmd->fd_in == -1)
	{
		ft_putendl_fd("no such file or directory", 2);
		shell->exit_status = 1;
		exit(shell->exit_status);
	}
	if (valid_builtins(cmd->argv[0]))
	{
		if (cmd->fd_in == -1 || cmd->fd_in == -1)
		{
			ft_putendl_fd("no such file or directory", 2);
			shell->exit_status = 1;
			exit(shell->exit_status);
		}
		built_ins2(shell, cmd);
		exit(shell->exit_status);
	}
	else
		execve(find_path(shell, cmd->argv[0]), cmd->argv, shell->env);
}
