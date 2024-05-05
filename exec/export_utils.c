/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:03:06 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/05 18:15:24 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	check_var(char *args)
{
	int	j;
	int	eq;

	j = 0;
	eq = 0;
	while (args[j])
	{
		if (args[j] == '=')
		{
			eq++;
			break ;
		}
		if (!(valid_var_name(args[j], j)
				|| args[j] == '=') || ft_isspace(args[j]))
		{
			return (0);
		}
		j++;
	}
	if (eq < 1)
		return (-1);
	return (1);
}

int	valid_export(char *args)
{
	int	i;

	i = 1;
	if (ft_strcmp(args, "export") != 0)
		return (0);
	while (args[i])
	{
		if (!valid_var_name(args[i], 0))
			return (0);
		if (!check_var(args))
			return (0);
		i++;
	}
	return (1);
}

void	update_environment(char **args, t_mini *shell)
{
	int	j;

	j = 1;
	while (args[j])
	{
		if (check_var(args[j]) == -1)
		{
			j++;
			continue ;
		}
		else if (!check_var(args[j]))
		{
			j++;
			continue ;
		}
		loop_through_env(shell, args[j], j);
		j++;
	}
}

void	export2(char **args, t_mini *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (args[j])
	{
		if (check_var(args[j]) == -1)
		{
			j++;
			continue ;
		}
		else if (check_var(args[j]) == 0)
		{
			shell->exit_status = 1;
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[j], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			j++;
			continue ;
		}
		while (shell->env[i++])
			update_environment(args, shell);
		j++;
	}
}
