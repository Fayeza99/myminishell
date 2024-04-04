/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:44:38 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/04 13:23:39 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// add all $ variables to a str
char	*add_variables(char **env, char *str)
{
	int		skip;
	int		i;
	char	**sub;

	sub = NULL;
	i = 0;
	while (str && str[i])
	{
		sub = ft_arr_realloc(sub, env_next(&str[i], env, &skip,\
			inside_quote(str, i) == 1));
		i += skip;
	}
	return (ft_arrjoin(sub));
}

// // add all $ variables to a str
// char	*add_variables(char **env, char *str)
// {
// 	int		count;
// 	int		i[2];
// 	char	**sub;
// 	char	*new;

// 	count = env_substrs(str, env);
// 	sub = (char **)malloc(sizeof(char *) * (count + 1));
// 	if (!sub)
// 		return (NULL);
// 	i[0] = 0;
// 	while (i[0] < count)
// 	{
// 		sub[i[0]++] = env_next(str, env, &i[1]);
// 		str += i[1];
// 	}
// 	sub[count] = NULL;
// 	return (ft_arrjoin(sub));
// }

// 	if not $ copy to arr[i] until $
// 	else
// 		if var exists strdup ft_getenv
// 		if $ ft_itoa getpid()
// 		if no var strdup "$"

// result not malloced
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

// result not malloced
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
