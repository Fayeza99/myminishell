/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:06:36 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/30 16:03:36 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_check(char *s)
{
	if (ft_strchr(s, '/') != NULL)
	{
		check_fd(s);
		if (access(s, F_OK) == 0)
		{
			if (access(s, X_OK) == 0)
				;
			else
				exit(126);
			return (0);
		}
		exit(127);
		return (0);
	}
	return (1);
}

void	file_check1(char *command)
{
	struct stat	path_stat;

	if (stat(command, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putendl_fd("is a directory", 2);
			exit(126);
		}
		else if (!(path_stat.st_mode & S_IXUSR))
		{
			exit(126);
		}
	}
}

void	handle_no_permission(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Permission denied", 2);
	free (cmd);
	exit(126);
}

void	handle_command_not_found(char *command)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

char	*check_permissions(char *cmd)
{
	if (access(cmd, X_OK) == 0)
	{
		return (cmd);
	}
	else
	{
		handle_no_permission(cmd);
		return (NULL);
	}
}