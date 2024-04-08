/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:49:45 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/08 11:34:02 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// see t_type enum in minishell.h
t_type	*get_type_arr(char **argv)
{
	int		i;
	t_type	*type;

	i = 0;
	type = (t_type *)malloc(sizeof(t_type) * (ft_arrlen(argv)));
	if (!type)
		return (NULL);
	while (argv && argv[i])
	{
		if (ft_strlen(argv[i]) < 2)
			type[i] = ARG;
		else if (argv[i][0] == argv[i][1] && argv[i][0] == '<')
			type[i] = HEREDOC;
		else if (argv[i][0] == argv[i][1] && argv[i][0] == '>')
			type[i] = APPEND;
		else if (argv[i][0] != argv[i][1] && argv[i][0] == '>')
			type[i] = OUT;
		else if (argv[i][0] != argv[i][1] && argv[i][0] == '<')
			type[i] = IN;
		else
			type[i] = ARG;
		i++;
	}
	return (type);
}

int	check_redir(char *str)
{
	int	skip;

	skip = 1;
	str++;
	if (*str == '>' || *str == '<')
	{
		if (*str != *(str - 1))
			return (0);
		skip = 2;
	}
	while (*str && is_whitespace(*str))
		str++;
	if ((!*str) || ((*str == '\"' || *str == '\'') && *str == *(str + 1)))
		return (0);
	return (skip);
}

int	valid_redir(char *str)
{
	int	redir;

	while (str && *str)
	{
		if (*str == '>' || *str == '<')
		{
			redir = check_redir(str);
			if (!redir)
				return (0);
			str += redir;
		}
		else
			str++;
	}
	return (1);
}

// replace old with new argv without quotes
char	**finalize_argv(char **old)
{
	char	**new;
	int		i;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (ft_arrlen(old) + 1));
	if (!new)
		return (NULL);
	while (old[i])
	{
		new[i] = remove_quotes(old[i]);
		i++;
	}
	new[i] = NULL;
	free(old);
	return (new);
}
