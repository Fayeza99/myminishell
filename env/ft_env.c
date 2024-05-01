/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:44:38 by asemsey           #+#    #+#             */
/*   Updated: 2024/05/01 13:14:49 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// replaces command with the expanded command
char	*ft_expand(t_mini *mini, char *command)
{
	char	*var;

	var = add_variables(mini, command);
	if (!var)
		return (NULL);
	free(command);
	return (var);
}

// add all $ variables to a str
char	*add_variables(t_mini *mini, char *str)
{
	int		skip;
	int		i;
	char	**sub;

	sub = NULL;
	i = 0;
	while (str && str[i])
	{
		sub = ft_arr_realloc(sub, env_next(mini, &str[i], &skip, \
			inside_quote(str, i) & S_QUOTE));
		i += skip;
	}
	return (ft_arrjoin(sub));
}

char	*ft_getenv(char *name, char **env, int freename)
{
	int		i;
	char	*var_name;
	char	*content;

	i = 0;
	while (env && env[i])
	{
		content = ft_strchr(env[i], '=');
		var_name = ft_substr(env[i], 0, content - env[i]);
		if (!ft_strcmp(var_name, name))
		{
			content++;
			if (freename)
				free(name);
			return (free(var_name), content);
		}
		free(var_name);
		i++;
	}
	if (freename)
		free(name);
	return (NULL);
}

// ft_getenv but with malloc
char	*ft_copyenv(char *name, char **env)
{
	int		i;
	char	*var_name;
	char	*content;

	i = 0;
	while (env && env[i])
	{
		content = ft_strchr(env[i], '=');
		var_name = ft_substr(env[i], 0, content - env[i]);
		if (!ft_strcmp(var_name, name))
		{
			content++;
			return (free(var_name), ft_strdup(content));
		}
		free(var_name);
		i++;
	}
	return (NULL);
}

int	in_env(char *name, char **env, int free_name)
{
	char	*var;

	var = ft_getenv(name, env, free_name);
	if (!var)
		return (0);
	return (1);
}
