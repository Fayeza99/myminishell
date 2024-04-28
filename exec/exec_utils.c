/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:23:57 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/28 14:35:30 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	forker(t_mini *shell, int i)
{
	shell->pids[i] = fork();
	if (shell->pids[i] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	initialize_multi_pipe(t_mini *shell)
{
	shell->pids = malloc(sizeof(pid_t) * count_cmd(shell) + 1);
}

void	cleanup_multi_pipe(t_mini *shell)
{
	free(shell->pids);
}

void	loop_through_commands(t_mini *shell, int **fd)
{
	t_list	*list;
	t_cmd	*cmd;
	int		i;

	list = shell->current_cmd;
	cmd = list->content;
	i = 0;
	while (i <= count_cmd(shell))
	{
		if (find_path(shell, cmd->argv[0]) == NULL)
		{
			i++;
			list = list->next;
			if (list != NULL)
				cmd = list->content;
			continue ;
		}
		forker(shell, i);
		if (!shell->pids[i])
			exec_helper(shell, fd, i, cmd);
		i++;
		list = list->next;
		if (list != NULL)
			cmd = list->content;
	}
}

void	wait_for_child_processes(t_mini *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i <= count_cmd(shell))
		waitpid(shell->pids[i++], &status, 0);
	shell->exit_status = WEXITSTATUS(status);
}
