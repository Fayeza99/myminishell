/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:26:05 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/23 17:10:14 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*find_path(char *s)
// {
// 	char	**all_path;
// 	char	*cmd;
// 	int		i;
// 	char	*tmp;

// 	all_path = ft_split(getenv("PATH"), ':');
// 	i = 0;
// 	tmp = ft_strjoin("/", s);
// 	while (all_path[i])
// 	{
// 		cmd = ft_strjoin(all_path[i++], tmp);
// 		if (access(cmd, X_OK) == 0)
// 			break;
// 		free(cmd);
// 	}
// 	free(tmp);
// 	ft_freearr(all_path);
// 	return (cmd);
// }

char	*my_getenv(t_mini *shell, char *s)
{
	char **vars;
	char *value = NULL;
	int i = 0;
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

// int	check_file(t_mini *shell, char *filename)
// {
// 	// if (access(filename, F_OK) == -1) {
//     //     // File doesn't exist
	
//     //     return 0;
//     // }

//     // Check execute permission
//     if (access(filename, X_OK) == -1) {
//         // Execute permission denied
// 		shell->exit_status = 127;
//         return 0;
//     }
// 	return (1);
// }

int		valid_builtins(char *s)
{
	if (ft_strcmp(s, "cd") == 0)
		return (1);
	else if (ft_strcmp(s, "export") == 0)
		return (1);
	if (ft_strcmp(s, "echo") == 0)
		return (1);
	else if (ft_strcmp(s, "pwd") == 0)
		return (1);
	else if (ft_strcmp(s, "unset") == 0)
		return (1);
	else if (ft_strcmp(s, "exit") == 0)
		return (1);
	return (0);
}

char *find_path(t_mini *shell, char *s)
{
	char	*path;
	char	**all_path;
	char	*cmd;
	int		i;
	char	*tmp;

	path = my_getenv(shell, "PATH");
	// path = getenv("PATH");

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
	if(!all_path[i] && !valid_builtins(s))
	{
		// printf("sdsdfsdfsdf\n");
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd(": command not found", 2);
		shell->exit_status = 127;
		free(tmp);
		ft_freearr(all_path);
		return NULL;
	}
	free(tmp);
	ft_freearr(all_path);
	return (cmd);
}
