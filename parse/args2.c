/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:49:45 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/17 13:59:06 by asemsey          ###   ########.fr       */
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

// replace old with new argv without quotes
t_list	*lst_argv(char **old)
{
	t_list	*new;
	int		i;

	i = 0;
	while (old[i])
	{
		if (!i)
			new = ft_lstnew(remove_quotes(old[i++]));
		else
			ft_lstadd_back(&new, ft_lstnew(remove_quotes(old[i++])));
	}
	free(old);
	return (new);
}
