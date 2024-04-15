/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:06:55 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/15 13:49:29 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		count_cmd(t_mini *shell)
{
	int i = 0;
	t_list *s;

	s = shell->current_cmd;
	while (s->next)
	{
		i++;
		s = s->next;
	}
	return (i);
}

int	**malloc_pipes(t_mini *shell)
{
	int	num_pipes = count_cmd(shell);
	if (num_pipes <= 0)
		return (NULL);
	
	int **pipes =(int **) malloc (sizeof(int *) * num_pipes + 1);
	int i = 0;
	if (!pipes)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (i <= num_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		if (pipe(pipes[i]) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipes);
}

void	piper(t_mini *shell, int **n, int j)
{
	int i = 0;
	while (i < count_cmd(shell))
	{
		if (j == i)
			pipe(n[i]);
		i++;
	}
}


void free_pipes(int **fd, int num_pipes)
{
	int i = 0;
	while (i < num_pipes)
	{
		free(fd[i]);
		i++;
	}
    // free(fd);
}

void	close_pipes(t_mini *shell, int **pipes)
{
	int i = 0;
	while (i < count_cmd(shell))
	{
		
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	
}

void	waiting(t_mini *shell)
{
	int i = 0;
	while (i < count_cmd(shell))
	{
		wait(NULL);
		i++;
	}
}

pid_t	create_child(t_mini *shell, int i)
{
	pid_t	pid;
	int k = 0;
	int j = count_cmd(shell);
	while (k < j)
	{
		if (k == i)
		{
			pid = fork();
		}
		k++;
	}
	return (pid);
}

void	exec_without_pipe(t_mini *shell)
{
	if (built_ins(shell))
		return ;
	t_cmd *cmd;
	cmd = shell->current_cmd->content;
	pid_t pid;
	pid = fork();
	if (!pid)
	{
		execve(find_path(cmd->argv[0]), cmd->argv, shell->env);
	}
	waitpid(pid, NULL, 0);
}

void	only_pipe(t_mini *shell)
{
	int	fd[2];
	pipe(fd);
	int pid;
	int pid2;
	t_cmd *cmd;
	cmd = shell->current_cmd->content;
	pid = fork();
	if (!pid)
	{
		// if (built_ins(shell))
		// 	exit(EXIT_SUCCESS);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(find_path(cmd->argv[0]), cmd->argv, shell->env);
	}
	shell->current_cmd = shell->current_cmd->next;
	cmd = shell->current_cmd->content;
	pid2 = fork();
	if (!pid2)
	{
		// if (built_ins(shell))
		// 	exit(EXIT_SUCCESS);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execve(find_path(cmd->argv[0]), cmd->argv, shell->env);
	}
	close(fd[1]);
	close(fd[0]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	exec_helper(t_mini *shell, int **fd, char **s, int i, t_cmd *cmd)
{
	if (i == 0)
	{
		dup2(fd[0][1], STDOUT_FILENO);
		// close(fd[0][0]);
		// close(fd[0][1]);
	}
	else if (i == count_cmd(shell))
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		// close(fd[i - 1][0]);
		// close(fd[i - 1][1]);
	}
	else
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		// close(fd[i - 1][1]);
		// close(fd[i - 1][0]);
		dup2(fd[i][1], STDOUT_FILENO);
		// close(fd[i][0]);
		// close(fd[i][1]);
	}
	int j = 0;
	while (j <= count_cmd(shell))
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	// printf("HOw many time huh?\n");
// t_cmd *cmd = (t_cmd *) shell->current_cmd->content;
// dprintf(2, "in = %d ---- out = %d\n", cmd->fd_in, cmd->fd_out);
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
	if (built_ins(shell))
		;
	else
	{
		execve(find_path(s[0]), s, shell->env);
	}
}

void	forker(t_mini *shell, int i)
{
	shell->pids[i] = fork();
	if (shell->pids[i] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	multi_pipe(t_mini *shell)
{
	t_cmd *cmd;
	t_list *list;
	list = shell->current_cmd;
	
	shell->pids = malloc (sizeof(pid_t) * count_cmd(shell) + 1);
	cmd = list->content;
	int	**fd;
	fd = malloc_pipes(shell);
	int i = 0;
	while (i <= count_cmd(shell))
	{
		forker(shell, i);
		if (!shell->pids[i])
		{
			exec_helper(shell, fd, cmd->argv, i, cmd);
		}
		else
		{
			i++;
			list = list->next;
			if (list != NULL)
				cmd = list->content;
		}
	}
	int j = 0;
	while (j <= count_cmd(shell))
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	
	free_pipes(fd, count_cmd(shell));
	while (waitpid(-1, NULL, 0) != -1)
		;
}


void m_exec(t_mini *shell)
{
	if (count_cmd(shell) == 0)
	{
		exec_without_pipe(shell);
		return;
	}
	else
	{
		// printf("exit :%d\n", shell->exit_status);
		multi_pipe(shell);
	}
    // return ;
}

