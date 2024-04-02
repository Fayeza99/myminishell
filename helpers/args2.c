/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:49:45 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/02 14:20:25 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_arg	*new_arg(char *arg)
// {
// 	t_arg	*new;

// 	new = (t_arg *)malloc(sizeof(t_arg));
// 	if (!new)
// 		return (NULL);
// 	new->arg = arg;
// 	new->type = ARG;
// 	return (new);
// }

// t_list	*get_argv(char *cmd)
// {
// 	char	**argv;
// 	t_list	*args;
// 	int		i;

// 	argv = get_argv_arr(cmd);
// 	i = 0;
// 	if (argv && argv[0])
// 		args = ft_lstnew((void *)new_arg(argv[i++]));
// 	while (argv && argv[i])
// 		ft_lstadd_back(&args, ft_lstnew((void *)new_arg(argv[i++])));
// 	free(argv);
// 	return (args);
// }

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
