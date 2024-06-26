/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:53:28 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/06 12:01:45 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_existing_variable(char *arg, t_mini *shell)
{
	int	l;

	l = 0;
	while (shell->env[l] != NULL)
	{
		if (ft_strncmp(shell->env[l], arg, ft_strchr(arg, '=') - arg + 1) == 0)
		{
			free(shell->env[l]);
			shell->env[l] = ft_strdup(arg);
			return (1);
		}
		l++;
	}
	return (0);
}

void	add_new_variable(char *arg, t_mini *shell)
{
	int		k;
	char	**new_ev;

	k = ft_arrlen(shell->env);
	new_ev = (char **)malloc(sizeof(char *) * (k + 2));
	if (!new_ev)
		return ;
	k = 0;
	while (shell->env[k])
	{
		new_ev[k] = ft_strdup(shell->env[k]);
		free(shell->env[k]);
		k++;
	}
	new_ev[k++] = ft_strdup(arg);
	new_ev[k] = NULL;
	free(shell->env);
	shell->env = new_ev;
}

void	loop_through_env(t_mini *shell, char *args, int j)
{
	int	l;

	l = 0;
	while (shell->env[l])
	{
		if (ft_strncmp(shell->env[l], args,
				ft_strchr(args, '=') - args + 1) == 0)
		{
			free(shell->env[l]);
			shell->env[l] = ft_strdup(args);
			j++;
		}
		l++;
	}
}

void	manage_env_variables(char **args, t_mini *shell)
{
	int	j;
	int	found;

	j = 1;
	while (args[j])
	{
		if (!check_var(args[j]) || check_var(args[j]) == -1)
		{
			j++;
			continue ;
		}
		found = update_existing_variable(args[j], shell);
		if (!found)
		{
			add_new_variable(args[j], shell);
		}
		j++;
	}
}

int	ex_export(t_mini *shell, char **args)
{
	int		i;

	if (ft_strcmp(args[0], "export") == 0 && !args[1])
	{
		i = 0;
		while (shell->env[i])
			printf ("declare -x %s\n", shell->env[i++]);
		return (0);
	}
	export2(args, shell);
	i = 0;
	while (shell->env[i++])
		manage_env_variables(args, shell);
	return (0);
}
