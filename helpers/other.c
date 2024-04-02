/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:52:01 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/02 14:21:46 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cmdprint(t_list *lst)
{
	t_cmd	*cont;

	while (lst)
	{
		cont = (t_cmd *)lst->content;
		printf("%s\n", cont->command);
		lst = lst->next;
	}
}

// void	ft_argprint(t_list *lst)
// {
// 	t_arg	*cont;

// 	while (lst)
// 	{
// 		cont = (t_arg *)lst->content;
// 		printf("%s, %d\n", cont->arg, cont->type);
// 		lst = lst->next;
// 	}
// }

char	*ft_freejoin(char *s1, char *s2)
{
	int		i;
	char	*s3;

	i = 1;
	if (s1)
		i += ft_strlen(s1);
	if (s2)
		i += ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * i);
	if (s3 == 0)
		return (0);
	s3[0] = '\0';
	if (s1 && s1[0] != 0)
		ft_strlcat(s3, s1, i);
	if (s2 && s2[0] != 0)
		ft_strlcat(s3, s2, i);
	free(s1);
	return (s3);
}
