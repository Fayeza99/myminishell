/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:03:06 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/29 10:32:42 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_str_arr(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	valid_var_name(char c, int index)
{
	if (index == 0)
	{
		if (!(ft_isalpha(c) || c == '_' ))
			return (0);
	}
	else
	{
		if (!(ft_isalnum(c) || c == '_' ))
			return (0);
	}
	return (1);
}

int	valid_export(char **args)
{
	int	i;
	int	j;

	i = 1;
	if (ft_strcmp(args[0], "export") != 0)
		return (0);
	while (args[i])
	{
		j = 1;
		if (!valid_var_name(args[i][0], 0))
			return (0);
		while (args[i][j])
		{
			if (args[i][j] == '=')
				break ;
			if (!(valid_var_name(args[i][j], j)
				|| args[i][j] == '=') || ft_isspace(args[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	update_environment(char **args, t_mini *shell)
{
	int	j;
	int	l;

	j = 1;
	l = 0;
	while (args[j])
	{
		l = 0;
		while (shell->env[l])
		{
			if (ft_strncmp(shell->env[l], args[j],
					ft_strchr(args[j], '=') - args[j] + 1) == 0)
			{
				free(shell->env[l]);
				shell->env[l] = ft_strdup(args[j++]);
				if (!args[j])
					return ;
			}
			l++;
		}
		j++;
	}
}

void	export2(char **args, t_mini *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		update_environment(args, shell);
		i++;
	}
}
