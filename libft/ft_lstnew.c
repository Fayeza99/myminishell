/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:52:18 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/16 18:26:14 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*x_node;

	x_node = malloc (sizeof(t_list));
	if (!x_node)
		return (NULL);
	if (!content)
	{
		x_node->content = NULL;
		x_node->next = NULL;
		return (x_node);
	}
	x_node->content = content;
	x_node->next = NULL;
	return (x_node);
}
