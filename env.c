/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:34:45 by asemsey           #+#    #+#             */
/*   Updated: 2024/03/25 14:40:17 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

char	*var_name(char *str);
int		valid_var_name(char c, int index);
int		var_len(t_mini *shell, char *str);
int		var_cat(t_mini *shell, char **new, char *name, int max_len);

// add all $ variables to a str
char	*add_variables(t_mini *shell, char *str)
{
	char	*new;
	int		len[2];

	len[0] = var_len(shell, str) + 1;
	if (len[0] - 1 < 1)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (len[0]));
	if (!new)
		return (NULL);
	len[1] = 0;
	while (str && *str)
	{
		if (*str == '$')
		{
			new[len[1]] = '\0';
			str++;
			str += var_cat(shell, &new, var_name(str), len[0]);
			len[1] = ft_strlen(new);
		}
		else
			new[len[1]++] = *str++;
	}
	new[len[1]] = '\0';
	return (new);
}

// get the name of the next var in str
char	*var_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (valid_var_name(str[i], i))
		i++;
	i++;
	name = (char *)malloc(sizeof(char) * (i));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, i);
	return (name);
}

// get the total len after replacing all $
int	var_len(t_mini *shell, char *str)
{
	char	*env;
	char	*name;
	int		len;

	len = 0;
	while (str && *str)
	{
		if (*str == '$')
		{
			name = var_name(++str);
			env = search_var(shell, name);
			if (!env)
				return (free(name), -1);
			len += ft_strlen(env);
			str += ft_strlen(name);
			free(env);
			free(name);
		}
		else
		{
			str++;
			len++;
		}
	}
	return (len);
}

// concatenates the 'name' variable to 'new'
int	var_cat(t_mini *shell, char **new, char *name, int max_len)
{
	char	*env;
	int		skip;

	env = search_var(shell, name);
	if (!env)
		return (free(name), -1);
	ft_strlcat(*new, env, max_len);
	skip = ft_strlen(name);
	free(name);
	free(env);
	return (skip);
}

// 1 for valid variable character
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

// int	main(void)
// {
// 	char *str = "echo $HOME$PATH	$USER";
// 	char *new = add_variables(str);
// 	printf("%s\n", new);
// 	free(new);
// 	system("leaks minishell");
// 	return (0);
// }

// test var_name():
// while (str && *str)
// {
// 	if (*str == '$')
// 		printf("%s\n", var_name(++str));
// 	str++;
// }

// test var_len():
// printf("%s | %d\n", str, var_len(str));