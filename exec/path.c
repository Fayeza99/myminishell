/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:26:05 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/05 17:49:02 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_getenv(t_mini *shell, char *s)
{
	char	**vars;
	char	*value;
	int		i;

	i = 0;
	while (shell->env[i])
	{
		vars = ft_split(shell->env[i], '=');
		if (ft_strcmp(vars[0], s) == 0)
		{
			value = ft_strdup(vars[1]);
			i++;
		}
		else
			i++;
		free_all(vars);
	}
	return (value);
}

char	*find_valid_command(t_mini *shell, char *command, char **all_path, char **env)
{
	char	*cmd_path;
	char	*tmp;
	char	*cmd;
	int		i;

	i = 0;
	file_check(command, env);
	tmp = ft_strjoin("/", command);
	while (all_path[i])
	{
		cmd = ft_strjoin(all_path[i], tmp);
		if (access(cmd, F_OK) == 0)
		{
			cmd_path = check_permissions(shell, cmd, env);
			if (cmd_path != NULL)
				break ;
		}
		free (cmd);
		i++;
	}
	if (!cmd_path && !valid_builtins(command))
		handle_command_not_found(shell, command);
	free (tmp);
	return (cmd_path);
}

char	*find_path(t_mini *shell, char *s)
{
	char	*path;
	char	**all_path;
	char	*cmd_path;

	if (ft_strncmp(s, "/", 1) == 0 || ft_strncmp(s, "./", 2) == 0
		|| ft_strncmp(s, "../", 3) == 0)
	{
		file_check(s, shell->env);
		if (check_permissions(shell, s, shell->env))
			return (s);
	}
	path = ft_getenv("PATH", shell->env, 0);
	all_path = ft_split(path, ':');
	cmd_path = find_valid_command(shell, s, all_path, shell->env);
	ft_freearr(all_path);
	return (cmd_path);
}
