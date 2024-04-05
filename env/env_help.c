/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:09:23 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/04 21:53:58 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		env_validchar(char c, int index);
char	*env_getname(char *str);

// copy the next portion of the expanded command
char	*env_next(char *str, char **env, int *skip, int inquotes)
{
	char	*next;
	char	*name;

	*skip = 1;
	next = NULL;
	if (*str == '$')
	{
		str++;
		if (!*str || is_whitespace(*str) || *str == '\'' || *str == '\"'
			|| inquotes)
			return (ft_strdup("$"));
		name = env_getname(str);
		*skip += ft_strlen(name);
		if (*name && *name == '$')
			return (free(name), ft_itoa((int)getpid()));
		else if ((!*name && !is_whitespace(*str)) || !in_env(name, env, 0))
			return (free(name), ft_strdup(""));
		else if (in_env(name, env, 0))
			return (free(name), ft_strdup(ft_getenv(env_getname(str), env, 1)));
	}
	if (!*str)
		return (NULL);
	while (str[*skip] && str[*skip] != '$')
		(*skip)++;
	return (ft_substr(str, 0, *skip));
}

// get the name of the next var in str
char	*env_getname(char *str)
{
	char	*name;
	int		i;

	if (!env_validchar(*str, 0) && *str != '$')
		return (NULL);
	i = 0;
	if (*str == '$')
		i++;
	while (env_validchar(str[i], i))
		i++;
	i++;
	name = (char *)malloc(sizeof(char) * (i));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, i);
	return (name);
}

// 1 for valid variable character
int	env_validchar(char c, int index)
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
