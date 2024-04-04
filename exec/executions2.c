/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:26:05 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/04 13:28:31 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	pipes(t_mini *shell)
{
	t_cmd	*cmd;
	int		fd[2];
	int		pid;
	int		pid2;

	if (shell->current_cmd->next)
	{
		cmd = (t_cmd *) shell->current_cmd->content;
		pipe(fd);
		pid = fork();
		if (!pid)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			execve(find_path((char *)cmd), cmd->argv, shell->env);
			exit(1);
		}
		pid2 = fork();
		if (!pid2)
		{
			cmd = (t_cmd *) shell->current_cmd->next;
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			execve(find_path((char *)cmd), cmd->argv, shell->env);
			exit(1);
		}
		close(fd[1]);
		close(fd[0]);
		waitpid(pid, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
}
