/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:43:59 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/23 10:33:36 by asemsey          ###   ########.fr       */
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
	if (*lst == rem)
		*lst = rem->next;
	tmp = *lst;
	while (tmp && *lst != rem)
	{
		if (tmp->next == rem)
		{
			tmp->next = rem->next;
			break ;
		}
		tmp = tmp->next;
	}
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

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		printf("---%s\n", (char *)lst->content);
		lst = lst->next;
	}
}
