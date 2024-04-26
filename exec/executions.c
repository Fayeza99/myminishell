/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:53:12 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/26 14:15:15 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ex_cd(char **args, t_mini *shell)
{
	int	i;
	char	cwd[1024];

	i = -1;
	if (ft_strcmp(args[0], "cd") != 0)
		return (0);

	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], "OLDPWD", ft_strchr(shell->env[i], '=') - shell->env[i]) == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != 0)
				shell->env[i++] = ft_strjoin("OLDPWD=", cwd);
		}
	}
	if (!args[1])
		chdir(getenv("HOME"));
	else
	{
		if (chdir(args[1]) != 0)
		{
			
			ft_putendl_fd(" No such file or directory", 2);
			shell->exit_status = 1;
		exit(shell->exit_status);

		}
		
	}
	i = -1;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], "PWD", ft_strchr(shell->env[i], '=') - shell->env[i]) == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != 0)
				shell->env[i++] = ft_strjoin("PWD=", cwd);
		}
	}
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
