/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:06:55 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/01 15:53:39 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pipes(int **fd, int num_pipes)
{
	int	i;

	i = 0;
	while (i <= num_pipes)
	{
		free(fd[i]);
		i++;
	}
}

void	close_pipes(t_mini *shell, int **pipes)
{
	int	i;

	i = 0;
	while (i < count_cmd(shell))
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	child_process(t_cmd *cmd, int *fd, t_mini *shell)
{
	if (fd[0] != STDIN_FILENO)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (fd[1] != STDOUT_FILENO)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	// if (valid_builtins(cmd->argv[0]))
	// {
	// 	execute_builtin(shell, cmd);
	// 	exit (shell->exit_status);
	// }
	if (find_path(shell, cmd->argv[0]) == NULL)
		exit (127);
	execve(find_path(shell, cmd->argv[0]), cmd->argv, shell->env);
}

void	parent_process(pid_t pid, t_mini *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	shell->exit_status = WEXITSTATUS(status);
}
