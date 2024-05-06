/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:06:36 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/06 12:51:24 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_check(char *s, char **env)
{
	char	*rel;

	if (!ft_strchr(s, '/'))
		return (1);
	check_fd(s);
	if (ft_strncmp(s, "./", 2) == 0 || ft_strncmp(s, "../", 3) == 0)
	{
		rel = ft_strjoin(ft_getenv("PWD", env, 0), "/");
		rel = ft_freejoin(rel, s);
		if (access(rel, F_OK) == 0 && access(rel, X_OK) == 0)
			return (free(rel), 0);
		if (access(rel, F_OK) == 0)
		{
			free(rel);
			exit(126);
		}
	}
	if (access(s, F_OK) == 0 && access(s, X_OK) == 0)
		return (0);
	if (access(s, F_OK) == 0)
		exit(126);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

void	file_check1(char *command)
{
	struct stat	path_stat;

	if (stat(command, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putendl_fd(": is a directory", 2);
			exit(126);
		}
		else if (!(path_stat.st_mode & S_IXUSR))
		{
			exit(126);
		}
	}
}

void	handle_no_permission(t_mini *shell, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Permission denied", 2);
	free (cmd);
	shell->exit_status = 126;
	exit(micro_free(shell));
}

void	handle_command_not_found(t_mini *shell, char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
	shell->exit_status = 127;
	exit(micro_free(shell));
}

char	*check_permissions(t_mini *shell, char *cmd, char **env)
{
	char	*rel;

	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0)
	{
		rel = ft_strjoin(ft_getenv("PWD", env, 0), "/");
		rel = ft_freejoin(rel, cmd);
		if (access(rel, X_OK) == 0)
			return (rel);
		handle_no_permission(shell, rel);
		return (NULL);
	}
	if (access(cmd, X_OK) == 0)
		return (cmd);
	handle_no_permission(shell, cmd);
	return (NULL);
}
