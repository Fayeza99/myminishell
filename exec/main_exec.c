/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:16:49 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/02 12:38:46 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	m_exec(t_mini *shell)
{
	if (!shell->command[0])
		return ;
	if (count_cmd(shell) == 0)
	{
		exec_without_pipe(shell);
	}
	else
	{
		multi_pipe(shell);
	}
}

void	multi_pipe(t_mini *shell)
{
	int	**fd;

	shell->pids = malloc(sizeof(pid_t) * count_cmd(shell) + 1);
	fd = malloc_pipes(shell);
	loop_through_commands(shell, fd);
	close_file_descriptors(fd, count_cmd(shell));
	free_pipes(fd, count_cmd(shell));
	free (fd);
	wait_for_child_processes(shell);
	free(shell->pids);
}

void	exec_helper(t_mini *shell, int **fd, int i, t_cmd *cmd)
{
	int	fd0;
	int	fd1;

	redirect_std_io(fd, i, shell);
	close_file_descriptors(fd, count_cmd(shell));
	fd0 = dup(STDIN_FILENO);
	fd1 = dup(STDOUT_FILENO);
	handle_fd_redirections(cmd);
	execute_command(shell, cmd);
	dup2(fd0, STDIN_FILENO);
	dup2(fd1, STDOUT_FILENO);
}

void	exec_without_pipe(t_mini *shell)
{
	t_cmd	*cmd;
	int		fd;
	int		fd1;

	shell->exit_status = 0;
	cmd = shell->current_cmd->content;
	if (!cmd->argv)
		return ;
	if (valid_builtins(cmd->argv[0]))
	{
		fd = dup(STDIN_FILENO);
		fd1 = dup(STDOUT_FILENO);
		handle_fd_redirections(cmd);
		execute_builtin(shell, cmd);
		dup2(fd, STDIN_FILENO);
		dup2(fd1, STDOUT_FILENO);
	}
	else
		execute_external(shell, cmd);
}
