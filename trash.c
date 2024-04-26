/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:26:05 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/26 14:18:19 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *find_path(char *s)
// {
// 	char	*path;
// 	char	**all_path;
// 	char	*cmd;
// 	int		i;
// 	char	*tmp;

// 	path = getenv("PATH");
// 	all_path = ft_split(path, ':');
// 	i = 0;
// 	tmp = ft_strjoin("/", s);
// 	while (all_path[i])
// 	{
// 		cmd = ft_strjoin(all_path[i], tmp);
// 		if (access(cmd, X_OK) == 0)
// 			break;
// 		free (cmd);
// 		i++;
// 	}
// 	return (cmd);
// }

void rando(char ** arr)
{
	int i = 0;

	while (arr[i])
	{
dprintf(2, "%s\n", arr[i]);
		i++;
	}
}

// void	pipes(t_mini *shell)
// {
// 	t_cmd	*cmd;
// 	int		fd[2];
// 	int		pid;
// 	int		pid2;

// 	if (shell->current_cmd->next)
// 	{
// 		cmd = (t_cmd *) shell->current_cmd->content;
// 		pipe(fd);
// 		pid = fork();
// // printf("11111\n");
// 		if (!pid)
// 		{
// // printf("<%s>\n", cmd->argv[1]);
// 			dup2(fd[1], 1);
// 			close(fd[0]);
// 			close(fd[1]);
// sleep(3);
// 			execve(find_path(cmd->argv[0]), cmd->argv, shell->env);
// 			// printf("kdjfk\n");
// 			// exit(1);
// 		}
// 		pid2 = fork();
// 		if (!pid2)
// 		{
// // printf("22222\n");
// 			shell->current_cmd = shell->current_cmd->next;
// 			cmd = (t_cmd *) shell->current_cmd->next;
// 			dup2(fd[0], 0);
// 			close(fd[0]);
// 			close(fd[1]);
// 			execve(find_path(cmd->argv[0]), cmd->argv, shell->env);
// 			// printf("kdjfk\n");
// 			// exit(1);
// 		}
// 		close(fd[1]);
// 		close(fd[0]);
// 		waitpid(pid, NULL, 0);
// 		waitpid(pid2, NULL, 0);
// // printf("kdjfk\n");
		
		
// 		// printf("here\n");
// 	}
// }



// void	pipes(t_mini *shell)
// {
// 	t_cmd	*cmd;
// 	int		fd[2];
// 	int		pid;
// 	int		pid2;

// 	if (shell->current_cmd->next)
// 	{
// 		cmd = (t_cmd *) shell->current_cmd->content;
// 		pipe(fd);
// 		pid = fork();
// 		if (!pid)
// 		{
// 			dup2(fd[1], 1);
// 			close(fd[0]);
// 			close(fd[1]);
// // rando((char **)shell->current_cmd->content);
// char **arr1 = malloc(sizeof(char *) * 3);
// arr1[0] = strdup("cat");
// arr1[1] = NULL;
// arr1[2] = NULL;

// // sleep(9999);
// execve(find_path(arr1[0]), arr1, shell->env);
// 			// execve("/bin/ls", (char **)shell->current_cmd->content, shell->env);
// 			// printf("jdhajd\n");
// 			exit(1);
// 		}
// 		pid2 = fork();
// 		if (!pid2)
// 		{

// char **arr2 = malloc(sizeof(char *) * 3);
// arr2[0] = strdup("ls");
// arr2[1] = NULL;
// arr2[2] = NULL;
// 			shell->current_cmd = shell->current_cmd->next;
// 			cmd = (t_cmd *) shell->current_cmd->next;
// 			dup2(fd[0], 0);
// 			close(fd[0]);
// 			close(fd[1]);
// // rando((char **)shell->current_cmd->content);
// // sleep(9999);
// execve(find_path(arr2[0]), arr2, shell->env);
// 			// execve("/usr/bin/wc", (char **)shell->current_cmd->content, shell->env);
// 			// printf("%s\n", find_path(cmd->argv[0]));
// 			exit(1);
// 		}
// 		close(fd[1]);
// 		close(fd[0]);
// 		waitpid(pid, NULL, 0);
// 		waitpid(pid2, NULL, 0);
// 		// printf("here\n");
// 	}
// }

int execute(t_cmd *cmd, t_mini *shell, int stdin)
{
	dup2(stdin, STDIN_FILENO);
	close(stdin);
	execve(find_path(cmd->argv[0]), cmd->argv, shell->env);
	return (1);
}

// void	pipes(t_mini *shell)
// {
// 	t_list	*lst;
// 	int		fd[2];
// 	int		stdin;

// 	stdin = dup(STDIN_FILENO);
// 	lst = shell->current_cmd;
// 	while (lst)
// 	{
// 		if (!lst->next)
// 		{
// 			if (!fork())
// 			{
// 				(void) execute((t_cmd *) lst->content, shell, stdin);
// 				// error
// 			}
// 			while (waitpid(-1 , 0, WUNTRACED) != -1)
// 				;			
// 			dup2(stdin, STDIN_FILENO);
// 			close(stdin);
// 		}
// 		else
// 		{
// 			pipe(fd);
// 			if (!fork())
// 			{
// 				close(fd[0]);
// 				dup2(fd[1], STDOUT_FILENO);
// 				close(fd[1]);
// 				(void) execute((t_cmd *) lst->content, shell, stdin);
// 				// error
// 			}
// 			close(fd[1]);
// 			close(stdin);
// 			stdin = fd[0];
// 		}
// 		lst = lst->next;
// 	}
// 	close(stdin);
// }



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
		shell->exit_status = 0;
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
	// find_path(shell, cmd->argv[0]);
	// if (shell->exit_status == 1 && !valid_builtins(cmd->argv[0]))
	// {
	// 		shell->exit_status = 1;
	// }
	if (!pid)
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
		
		execve(find_path(shell, cmd->argv[0]), cmd->argv, shell->env);
	}
	waitpid(pid, NULL, 0);
}


void redirect_std_io(int **fd, int i, t_mini *shell)
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

void close_file_descriptors(int **fd, int cmd_count)
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

void handle_fd_redirections(t_cmd *cmd)
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

void execute_command(t_mini *shell, t_cmd *cmd)
{
	if (valid_builtins(cmd->argv[0]))
	{
		built_ins2(shell, cmd);
		exit(0);
	}
	else
	{
		execve(find_path(shell, cmd->argv[0]), cmd->argv, shell->env);
	}
}

void exec_helper(t_mini *shell, int **fd, char **s, int i, t_cmd *cmd)
{
	(void)s;
	redirect_std_io(fd, i, shell);
	close_file_descriptors(fd, count_cmd(shell));
	handle_fd_redirections(cmd);
	execute_command(shell, cmd);
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

void initialize_multi_pipe(t_mini *shell)
{
	shell->pids = malloc(sizeof(pid_t) * count_cmd(shell) + 1);
}

void cleanup_multi_pipe(t_mini *shell)
{
	free(shell->pids);
}

void loop_through_commands(t_mini *shell, int **fd)
{
	t_list *list = shell->current_cmd;
	t_cmd *cmd = list->content;
	int i = 0;
	while (i <= count_cmd(shell))
	{
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
			exec_helper(shell, fd, cmd->argv, i, cmd);
		i++;
		list = list->next;
		if (list != NULL)
			cmd = list->content;
	}
}


void wait_for_child_processes(t_mini *shell)
{
	int i;
	
	i = 0;
	while (i <= count_cmd(shell))
		waitpid(shell->pids[i++], NULL, 0);
}

void multi_pipe(t_mini *shell)
{
	initialize_multi_pipe(shell);
	int **fd = malloc_pipes(shell);
	loop_through_commands(shell, fd);
	close_file_descriptors(fd, count_cmd(shell));
	free_pipes(fd, count_cmd(shell));
	wait_for_child_processes(shell);
	cleanup_multi_pipe(shell);
}


void m_exec(t_mini *shell)
{
	if (!shell->command[0])
		return ;
	if (count_cmd(shell) == 0)
	{
		
		exec_without_pipe(shell);
		// printf("here --- %d\n", shell->flag);

		return;
	}
	else
	{
		// printf("exit :%d\n", shell->exit_status);
		multi_pipe(shell);
	}
}

