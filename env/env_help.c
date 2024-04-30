/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:09:23 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/30 13:11:55 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		env_validchar(char c, int index);
char	*env_getname(char *str);
char	*env_special(t_mini *mini, char c);

// copy the next portion of the expanded command
char	*env_next(t_mini *mini, char *str, int *skip, int inquotes)
{
	char	*name;

	*skip = 1;
	if (*str && *str == '$')
	{
		str++;
		if (!*str || is_whitespace(*str) || *str == '\'' || *str == '\"'
			|| inquotes)
			return (ft_strdup("$"));
		name = env_getname(str);
		*skip += ft_strlen(name);
		if (!name)
			return (ft_strdup(""));
		else if (*name && (*name == '$' || *name == '?'))
			return (free(name), env_special(mini, *name));
		else if ((!*name && !is_whitespace(*str))
			|| !in_env(name, mini->env, 0))
			return (free(name), ft_strdup(""));
		else if (in_env(name, mini->env, 0))
			return (free(name), ft_strdup(ft_getenv(env_getname(str) \
				, mini->env, 1)));
	}
	while (*str && str[*skip] && str[*skip] != '$')
		(*skip)++;
	return (ft_substr(str, 0, *skip));
}

// $$ is the shell pid, $? is the exit code of the last command
char	*env_special(t_mini *mini, char c)
{
	if (c == '$')
		return (ft_itoa((int)getpid()));
	if (c == '?')
		return (ft_itoa(mini->exit_status));
	return (NULL);
}

// get the name of the next var in str
char	*env_getname(char *str)
{
	char	*name;
	int		i;

	if (!*str)
		return (NULL);
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' ))
		i++;
	if (*str == '$' || *str == '?')
		i = 1;
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
