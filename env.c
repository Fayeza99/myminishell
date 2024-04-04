/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:09:23 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/03 17:14:20 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		var_len(char **env, char *str);
int		var_cat(char **env, char **new, char *name, int max_len);
int		valid_var(char c, int index);
int		in_env(char *name, char **env, int free_name);
char	*var_name(char *str);

// add all $ variables to a str
char	*add_variables(char **env, char *str)
{
	(void)env;
	(void)str;
	// count the added variables plus strings between (ft)
	// malloc array
	// while i < arrlen
	// 	if not $ copy to arr[i] until $
	// 	else
	// 		if var exists strdup ft_getenv
	// 		if $ ft_itoa getpid()
	// 		if no var strdup "$"
	// arr[i] = NULL
	// new = ft_arrjoin(arr)
	return (NULL);
}

// add all $ variables to a str
// char	*add_variables(char **env, char *str)
// {
// 	char	*new;
// 	int		len[3];

// 	len[0] = var_len(env, str) + 1;
// 	if (len[0] - 1 < 1)
// 		return (NULL);
// 	new = (char *)malloc(sizeof(char) * (len[0]));
// 	if (!new)
// 		return (NULL);
// 	len[1] = 0;
// 	len[2] = 0;
// 	while (str && str[len[2]])
// 	{
// 		if (str[len[2]] == '$' && inside_quote(str, len[2]) != 1 && in_env(var_name(str[len[2] + 1]), env, 1))
// 		{
// 			new[len[1]] = '\0';
// 			len[2]++;
// 			len[2] += var_cat(env, &new, var_name(&str[len[2]]), len[0]);
// 			len[1] = ft_strlen(new);
// 		}
// 		else
// 			new[len[1]++] = str[len[2]++];
// 	}
// 	new[len[1]] = '\0';
// 	return (new);
// }

int	count_var_arr(char *str, char **env)
{
	int	count;

	count = 0;
	while (str && *str)
	{
		if (*str == '$')
		{
			str++;
			if (*str && !is_whitespace(*str) && !in_env(var_name(str), env, 1))
				str++;
			else
				count++;
			if (*str == '$')
				str++;
			else
			{
				if (valid_var(*str, 0))
					str++;
				while (valid_var(*str, 1))
					str++;
			}
			if (*str)
				count++;
		}
		else
			str++;
	}
	return (count);
}

// result not malloced
char	*ft_getenv(char *name, char **env)
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
			return (free(var_name), content);
		}
		free(var_name);
		i++;
	}
	return (NULL);
}

// get the total len after replacing all $
int	var_len(char **env, char *str)
{
	char	*var;
	char	*name;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && inside_quote(str, i) != 1)
		{
			name = var_name(&str[++i]);
			var = ft_getenv(name, env);
			if (!var)
				continue ;
			len += ft_strlen(var);
			i += ft_strlen(name);
			free(name);
			continue ;
		}
		i++;
		len++;
	}
	return (len);
}

// concatenates the 'name' variable to 'new'
int	var_cat(char **env, char **new, char *name, int max_len)
{
	char	*var;
	int		skip;

	var = ft_getenv(name, env);
	if (!var)
		return (free(name), -1);
	ft_strlcat(*new, var, max_len);
	skip = ft_strlen(name);
	free(name);
	// free(var);
	return (skip);
}

// get the name of the next var in str
char	*var_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (valid_var(str[i], i))
		i++;
	i++;
	name = (char *)malloc(sizeof(char) * (i));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, i);
	return (name);
}

int	in_env(char *name, char **env, int free_name)
{
	char	*var;

	var = ft_getenv(name, env);
	if (free_name)
		free(name);
	if (!var)
		return (0);
	return (1);
}

// 1 for valid variable character
int	valid_var(char c, int index)
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

// int	main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	char **new_env = ft_arrdup(env);
// 	// char *new = add_variables(new_env, "\"\'$USER$USER\'\"");
// 	// printf("--%s--\n", new);
// 	printf("--%d--\n", count_var_arr("heyyyyyy", new_env));
// 	return 0;
// }