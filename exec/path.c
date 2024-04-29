/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:26:05 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/29 12:13:53 by fnikzad          ###   ########.fr       */
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

char	*find_valid_command(char *command, char **all_path)
{
	char	*cmd_path;
	char	*tmp;
	char	*cmd;
	int		i;

	i = 0;
	tmp = ft_strjoin("/", command);
	while (all_path[i])
	{
		cmd = ft_strjoin(all_path[i], tmp);
		if (access(cmd, F_OK) == 0)
		{
			cmd_path = check_permissions(cmd);
			if (cmd_path != NULL)
			{
				break ;
			}
		}
		free (cmd);
		i++;
	}
	// free (cmd);
	free (tmp);
	if (!cmd_path && !valid_builtins(command))
		handle_command_not_found(command);
	return (cmd_path);
}

char	*find_path(t_mini *shell, char *s)
{
	char	*path;
	char	**all_path;
	char	*cmd_path;

	if (!file_check(shell, s))
		return (NULL);
	path = my_getenv(shell, "PATH");
	all_path = ft_split(path, ':');
	free (path);
	cmd_path = find_valid_command(s, all_path);
	ft_freearr(all_path);
	return (cmd_path);
}
