/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:06:55 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/23 15:04:42 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		count_cmd(t_mini *shell)
{
	t_cmd *cmd = shell->current_cmd->content;
	int i = 0;
	t_list *s;

	if (cmd->command[0] == '\0')
	{
		// printf("here\n");
		return (-1);
	}
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
	int **pipes =(int **) malloc (sizeof(int *) * (num_pipes + 1));
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
	while (i <= num_pipes)
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
	
	int *fd = (int*)malloc(sizeof(int) * 2);
	t_cmd *cmd;
	cmd = shell->current_cmd->content;
	if (valid_builtins(cmd->argv[0]))
	{
		built_ins2(shell, cmd);
		return ;
	}
	fd[0] = cmd->fd_in;
	fd[1] = cmd->fd_out;
	if (fd[0] == -1 || fd[1] == -1)
	{
		ft_putendl_fd("no such file or directory", 2);
		shell->exit_status = 1;
		return ;
	}
	pid_t pid;
	pid = fork();
	if (!pid)
	{
		// printf("%d\n", cmd->fd_in);
		// printf("%d\n", cmd->fd_out);
		
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
		execve(find_path(shell, cmd->argv[0]), cmd->argv, shell->env);
	}
	// printf("here\n");
	// close(fd[1]);
	// close(fd[0]);
	// free()(cmd->fd_out);
	// free(cmd->fd_in);
	waitpid(pid, NULL, 0);
}



void	exec_helper(t_mini *shell, int **fd, char **s, int i, t_cmd *cmd)
{
	(void)s;
	if (i == 0)
	{
		if (dup2(fd[i][1], STDOUT_FILENO) == -1)
			perror("");
	}
	else if (i == count_cmd(shell))
	{
		// printf("world\n");
		// printf("%d\n", STDOUT_FILENO);

		dup2(fd[i - 1][0], STDIN_FILENO);
	}
	else
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		dup2(fd[i][1], STDOUT_FILENO);
	}
	int j = 0;
	while (j <= count_cmd(shell))
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
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

	if (valid_builtins(cmd->argv[0]))
	{
		built_ins2(shell, cmd);
		exit(0);
	}
	else
	{
		// printf("%s\n", cmd->argv[0]);
		execve(find_path(shell, cmd->argv[0]), cmd->argv, shell->env);
	}
}



// void	exec_helper(t_mini *shell, int **fd, char **s, int i, t_cmd *cmd)
// {
	
// 	if (i == 0)
// 	{

		
		
// 		printf("%d\n", fd[0][0]);
// 		printf("%d\n", fd[0][1]);
		
// 		dup2(fd[i][1], STDOUT_FILENO);
// 		// close(fd[i][1]);
		
// 	}
// 	// printf("------%d\n", STDOUT_FILENO);
// 	if (i == count_cmd(shell))
// 	{
// 		dup2(fd[i - 1][0], STDIN_FILENO);
// 	}
// 	else
// 	{
// 		dup2(fd[i - 1][0], STDIN_FILENO);
// 		dup2(fd[i][1], STDOUT_FILENO);
// 	}

// 	int j = 0;
// 	while (j <= count_cmd(shell))
// 	{
// 		close(fd[j][0]);
// 		close(fd[j][1]);
// 		j++;
// 	}
// 	if (cmd->fd_in != STDIN_FILENO)
// 	{
// 		dup2(cmd->fd_in, STDIN_FILENO);
// 		close(cmd->fd_in);
// 	}
// 	if (cmd->fd_out != STDOUT_FILENO)
// 	{

// 		dup2(cmd->fd_out, STDOUT_FILENO);
// 		close(cmd->fd_out);
// 	}
// 	if (built_ins(shell))
// 		exit(0);
// 	else
// 	{
// 		execve(find_path(shell, s[0]), s, shell->env);
// 	}
// }

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
		// if (valid_builtins(cmd->argv[0]))
		// {
		// 	i++;
		// 	list = list->next;
		// 	if (list != NULL)
		// 		cmd = list->content;
		// 	continue;
		// }
		// if (ft_strcmp(cmd->argv[0], "exit") == 0)
		// 	exit(shell->exit_status);
		if (find_path(shell, cmd->argv[0]) == NULL)
		{
			i++;
			list = list->next;
			if (list != NULL)
				cmd = list->content;
			continue;
		}
		forker(shell, i);
		if (!shell->pids[i])
		{
			
			exec_helper(shell, fd, cmd->argv, i, cmd);
		}
		i++;
		list = list->next;
		if (list != NULL)
			cmd = list->content;
	}
	int j = 0;
	while (j <= count_cmd(shell))
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	free_pipes(fd, count_cmd(shell));
	i = 0;
	while (i <= count_cmd(shell))
		waitpid(shell->pids[i++], NULL, 0);
}


void m_exec(t_mini *shell)
{
	// int count = count_cmd(shell);
	// if (count == -1)
	// 	return ;
	// if (shell->command == NULL)
	// 	return ;
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

