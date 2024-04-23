/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:49:45 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/22 15:02:00 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// see t_type enum in minishell.h
t_type	*get_type_arr(t_list *argv)
{
	int		i;
	t_type	*type;
	char	*str;

	i = 0;
	type = (t_type *)malloc(sizeof(t_type) * (ft_lstsize(argv)));
	if (!type)
		return (NULL);
	while (argv)
	{
		str = argv->content;
		if (str[0] == str[1] && str[0] == '<')
			type[i] = HEREDOC;
		else if (str[0] == str[1] && str[0] == '>')
			type[i] = APPEND;
		else if (str[0] != str[1] && str[0] == '>')
			type[i] = OUT;
		else if (str[0] != str[1] && str[0] == '<')
			type[i] = IN;
		else
			type[i] = ARG;
		i++;
		argv = argv->next;
	}
	return (type);
}

// replace old with new argv without quotes
void	unquote_argv(t_list **argv)
{
	t_list	*lst;
	char	*str;

	lst = *argv;
	while (lst)
	{
		str = remove_quotes((char *)lst->content);
		free(lst->content);
		lst->content = str;
		lst = lst->next;
	}
}
