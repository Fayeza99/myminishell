/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:43:59 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/15 15:34:08 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_lst_toarr(t_list *lst)
{
	char	**new;
	int		i;

	if (!lst)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (lst)
	{
		new[i++] = lst->content;
		lst = lst->next;
	}
	new[i] = NULL;
	return (new);
}

void	ft_lst_remove(t_list **lst, t_list *rem, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !rem)
		return ;
	tmp = *lst;
	while (tmp)
	{
		if (tmp->next == rem)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	tmp->next = rem->next;
	if (del)
		(*del)(rem->content);
	free(rem);
}

void	ft_lst_delall(t_list **lst, void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;

	if (!lst)
		return ;
	head = *lst;
	while (head)
	{
		tmp = head->next;
		if (del)
			(*del)(head->content);
		free(head);
		head = tmp;
	}
	*lst = NULL;
}
