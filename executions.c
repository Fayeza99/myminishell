/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:53:12 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/03 12:21:05 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmd *cmd = mini->current_cmd->content;
// t_cmd *cmd2 = mini->current_cmd->next->content;
// printf("%s\n%s\n", cmd->command, cmd2->command);


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
			perror("cd");
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

// void	exec_builtins(t_mini *shell)
// {
// 	// if(ft_strcmp(shell->argv[0], "cd") == 0)
// }



void	exec_cmd(t_mini *cmds)
{
	char **new_c;
	char **all_paths;
	char *path;
	char *cmd;

	path = getenv("PATH");
	all_paths = ft_split(path, ':');
	new_c = ft_split(cmds->command, ' ');
	ex_cd(new_c, cmds);
	ex_export(cmds, new_c);
	int k = 0;
	char *temp;
	pid_t pid = fork();
	if (!pid)
	{
		
		k = 0;
		temp = ft_strjoin("/", new_c[0]);
		while (all_paths[k])
		{
			cmd = ft_strjoin(all_paths[k], temp);
			if (access(cmd, X_OK) == 0)
				break;
			k++;
			free (cmd);
		}
		if (all_paths[k] == NULL)
		{
			printf("cmd not found");
			return ;
		}
		execve(cmd, new_c, cmds->env);
		// pipes(cmds);
	}
	waitpid(pid, 0, 0);

}
