/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:02:33 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/17 12:58:29 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	head = *lst;
	while (head != 0)
	{
		tmp = head->next;
		(*del)(head->content);
		free (head);
		head = tmp;
	}
	*lst = NULL;
}
