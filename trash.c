/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:26:05 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/08 15:07:23 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_path(char *s)
{
	char	*path;
	char	**all_path;
	char	*cmd;
	int		i;
	char	*tmp;

	path = getenv("PATH");
	all_path = ft_split(path, ':');
	i = 0;
	tmp = ft_strjoin("/", s);
	while (all_path[i])
	{
		cmd = ft_strjoin(all_path[i], tmp);
		if (access(cmd, X_OK) == 0)
			break;
		free (cmd);
		i++;
	}
	return (cmd);
}

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