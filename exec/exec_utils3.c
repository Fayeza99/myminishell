/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:28:01 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/28 14:40:16 by fnikzad          ###   ########.fr       */
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

void	allocate_memory_for_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i <= num_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	create_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i <= num_pipes)
	{
		if (pipe(pipes[i]) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	**malloc_pipes(t_mini *shell)
{
	int	num_pipes;
	int	**pipes;

	num_pipes = count_cmd(shell);
	if (num_pipes <= 0)
		return (NULL);
	pipes = (int **)malloc(sizeof(int *) * (num_pipes + 1));
	if (!pipes)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	allocate_memory_for_pipes(pipes, num_pipes);
	create_pipes(pipes, num_pipes);
	return (pipes);
}
