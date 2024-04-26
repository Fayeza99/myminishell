/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:26:05 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/26 14:39:11 by fnikzad          ###   ########.fr       */
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

int	file_check(t_mini *shell, char *s)
{
	if (ft_strchr(s, '/') != NULL)
	{
		check_fd(shell, s);
		if (access(s, F_OK) == 0)
		{
			if(access(s, X_OK) == 0)
			{
				;
			}
			else
				shell->exit_status = 126;
			return 0;
		}
		shell->exit_status = 127;
		return 0;
	}
	return (1);
}


void	file_check1(char *command, t_mini *mini)
{
	struct stat	path_stat;

	if (stat(command, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putendl_fd("is a directory", 2);
			mini->exit_status = 126;
			return ;
			
		}
		else if (!(path_stat.st_mode & S_IXUSR))
		{
			mini->exit_status = 126;
			exit(mini->exit_status);
			return ;
			
		}
	}
}

char *find_path(t_mini *shell, char *s)
{
	char	*path;
	char	**all_path;
	char	*cmd;
	int		i;
	char	*tmp;

	// t_cmd *command = shell->current_cmd->content;
	
	if (!file_check(shell, s))
		return NULL;
	
	path = my_getenv(shell, "PATH");
	// path = getenv("PATH");

	all_path = ft_split(path, ':');
	i = 0;
	tmp = ft_strjoin("/", s);
	while (all_path[i])
	{
		// file_check1(tmp, shell);
		cmd = ft_strjoin(all_path[i], tmp);
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
			{
				// exit(0);
				break;
			}
			shell->exit_status = 126;
		}
		free (cmd);
		i++;
	}
	if(!all_path[i] && !valid_builtins(s))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd(": command not found", 2);
		shell->exit_status = 127;
		free(tmp);
		ft_freearr(all_path);
		return NULL;
	}
	shell->exit_status = 0;
	
	free(tmp);
	ft_freearr(all_path);
	return (cmd);
}


// if (access(all_path[i], F_OK) == 0)
// 		{
// 			if (access(all_path[i], X_OK) == 0)
// 				return NULL;
// 			shell->exit_status = 126;
// 		}