/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:53:28 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/08 15:01:39 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	len_str_arr(char **s)
// {
// 	int	i;

// 	i = 0;
// 	while (s && s[i])
// 		i++;
// 	return (i);
// }

// int	valid_var_name(char c, int index)
// {
// 	if (index == 0)
// 	{
// 		if (!(ft_isalpha(c) || c == '_' ))
// 			return (0);
// 	}
// 	else
// 	{
// 		if (!(ft_isalnum(c) || c == '_' ))
// 			return (0);
// 	}
// 	return (1);
// }

int	valid_export(char **args)
{
	int	i;
	int	eq;
	int	j;

	i = 1;
	eq = 0;
	if (ft_strcmp(args[0], "export") != 0)
		return (0);
	while (args[i])
	{
		j = 1;
		if (!env_validchar(args[i][0], 0))
			return (0);
		while (args[i][j])
		{
			if (args[i][j] == '=')
				eq++;
			// if (!(ft_isalpha(args[i][0]) || args[i][0] == '_' ))
			// 	return (0);
			// if (!(ft_isalnum(args[i][j]) || args[i][j] == '_' || (j > 0 && args[i][j] == '=')))
			// 	return (0);
			if (!(env_validchar(args[i][j], j) || args[i][j] == '='))
				return (0);
			j++;
		}
		i++;
	}
	if (eq != i - 1)
		return (0);
	return (1);
}

int	ex_export(t_mini *shell, char **args)
{
	int		j;
	int		l;

	if (ft_strcmp(args[0], "export"))
		return (1);
	j = 0;
	if (!args[1])
	{
		while (shell->env[j])
			printf ("declare -x %s\n", shell->env[j++]);
		return (0);
	}
	// this line has reversed meaning...
	if (!valid_export(args))
	{
		write(1, "not export syntax\n", 18);
		return (0);
	}
	j = 1;
	while (args[j])
	{
		l = 0;
		while (shell->env[l])
		{
			if (ft_strncmp(shell->env[l], args[j], ft_strchr(args[j], '=') - args[j] + 1) == 0)
			{
				free(shell->env[l]);
				shell->env[l] = ft_strdup(args[j++]);
				l = 0;
				if (!args[j])
					return (0);
			}
			l++;
		}
		shell->env = ft_arr_realloc(shell->env, args[j++]);
	}
	return (0);
}

// int	ex_export(t_mini *shell, char **args)  
// {
// 	int		i;
// 	int		j;
// 	int		l;
// 	char	**new_ev;

// 	if (ft_strcmp(args[0], "export") == 0 && !args[1])
// 	{
// 		i = 0;
// 		while (shell->env[i])
// 			printf ("declare -x %s\n", shell->env[i++]);
// 		return (0);
// 	}
// 	if (valid_export(args) == 0)
// 	{
// 		write(1, "not export syntax\n", 18);
// 		return (0);
// 	}
// 	i = 0;
// 	// while (shell->env[i] != NULL)
// 	// {
// 		// j = 1;
// 		// while (args[j])
// 		// {
// 		// 	l = 0;
// 		// 	while (shell->env[l])
// 		// 	{
// 		// 		if (ft_strncmp(shell->env[l], args[j], ft_strchr(args[j], '=') - args[j] + 1) == 0)
// 		// 		{
// 		// 			free (shell->env[l]);
// 		// 			shell->env[l] = ft_strdup(args[j++]);
// 		// 			if (!args[j])
// 		// 				return (0);
// 		// 		}
// 		// 		l++;
// 		// 	}
// 		// 	j++;
// 		// }
// 		// i++;
// 	// }
// 	// i = 0;
// 	while (shell->env[i])
// 	{
// 		j = 1;
// 		while (args[j])
// 		{
// 			l = 0;
// 			while (shell->env[l])
// 			{
// 				if (ft_strncmp(shell->env[l], args[j], ft_strchr(args[j], '=') - args[j] + 1) == 0)
// 				{
// 					free (shell->env[l]);
// 					shell->env[l] = ft_strdup(args[j++]);
// 					l = 0;
// 					if (!args[j])
// 						return (0);
// 				}
// 				l++;
// 			}
// 			shell->env = ft_arr_realloc(shell->env, args[j++]);
// 			if (!args[j])
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// for this line: shell->env = ft_arr_realloc(shell->env, args[j++]);
	// int k = ft_arrlen(shell->env);
	// new_ev = (char **) malloc (sizeof(char *) * (k + 2));
	// if (!new_ev)
	// 	return (-1);
	// k = 0;
	// while (shell->env[k])
	// {
	// 	new_ev[k] = ft_strdup(shell->env[k]);
	// 	k++;
	// }
	// new_ev[k++] = ft_strdup(args[j++]);
	// new_ev[k] = NULL;
	// shell->env = new_ev;