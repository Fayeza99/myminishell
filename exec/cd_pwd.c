/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:53:12 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/02 11:37:08 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_oldpwd(t_mini *shell)
{
	char	cwd[1024];
	int		i;

	i = -1;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], "OLDPWD",
				ft_strchr(shell->env[i], '=') - shell->env[i]) == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != 0)
				shell->env[i++] = ft_strjoin("OLDPWD=", cwd);
		}
	}
}

void	change_directory(char *path, t_mini *shell)
{
	if (chdir(path) != 0)
	{
		ft_putendl_fd(" No such file or directory", 2);
		shell->exit_status = 1;
	}
}

void	update_pwd(t_mini *shell)
{
	char	cwd[1024];
	int		i;

	i = -1;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], "PWD",
				ft_strchr(shell->env[i], '=') - shell->env[i]) == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != 0)
				shell->env[i++] = ft_strjoin("PWD=", cwd);
		}
	}
}

int	ex_cd(char **args, t_mini *shell)
{
	if (ft_strcmp(args[0], "cd") != 0)
		return (0);
	update_oldpwd(shell);
	if (!args[1])
		change_directory(getenv("HOME"), shell);
	else
		change_directory(args[1], shell);
	update_pwd(shell);
	return (0);
}

int	ex_pwd(char **args)
{
	char	cwd[1024];

	if (ft_strncmp(args[0], "pwd", 3) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != 0)
			printf("%s\n", cwd);
		else
			perror("failed");
	}
	return (0);
}
