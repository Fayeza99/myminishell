/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:12:09 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/28 14:34:05 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_newline1(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-')
		i++;
	else
		return (0);
	while (s[i])
	{
		if (s[i] == 'n')
			i++;
		else
			return (0);
	}
	return (i);
}

int	check_newline(char **s)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (check_newline1(s[j]))
	{
		i = 0;
		if (s[j][0] == '-')
			i++;
		while (s[j][i])
		{
			if (s[j][i] == 'n')
				i++;
			else
				return (0);
		}
		j++;
	}
	return (j);
}

void	echo_arguments(char **argv, int fd_out, int start_index, int newline)
{
	int	i;

	i = start_index;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], fd_out);
		if (argv[i + 1])
			ft_putstr_fd(" ", fd_out);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", fd_out);
}

int	determine_start_index(char **argv, int newline)
{
	int	i;

	i = 0;
	if (ft_strcmp(argv[0], "echo") == 0)
	{
		if (check_newline1(argv[1]))
			newline = 1;
		if (argv[1] && argv[newline] && (check_newline(argv) != 0))
			i = newline;
		else if (argv[1] && !argv[newline] && (check_newline(argv) != 0))
			return (0);
		else
			i = 1;
	}
	return (i);
}

int	ex_echo(t_mini *shell, t_cmd *cmd)
{
	int	j;
	int	start_index;

	(void)shell;
	j = check_newline(cmd->argv);
	if (!cmd->argv[1])
	{
		printf("\n");
		return (0);
	}
	j = check_newline(cmd->argv);
	start_index = determine_start_index(cmd->argv, j);
	echo_arguments(cmd->argv, cmd->fd_out, start_index, j);
	return (0);
}
