/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:16:49 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/29 12:12:48 by fnikzad          ###   ########.fr       */
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

	initialize_multi_pipe(shell);
	fd = malloc_pipes(shell);
	loop_through_commands(shell, fd);
	close_file_descriptors(fd, count_cmd(shell));
	free_pipes(fd, count_cmd(shell));
	free (fd);
	wait_for_child_processes(shell);
	cleanup_multi_pipe(shell);
}

void	exec_helper(t_mini *shell, int **fd, int i, t_cmd *cmd)
{
	redirect_std_io(fd, i, shell);
	close_file_descriptors(fd, count_cmd(shell));
	handle_fd_redirections(cmd);
	execute_command(shell, cmd);
}

void	exec_without_pipe(t_mini *shell)
{
	t_cmd	*cmd;

	cmd = shell->current_cmd->content;
	if (valid_builtins(cmd->argv[0]))
	{
		execute_builtin(shell, cmd);
	}
	else
	{
		execute_external(shell, cmd);
	}
}
