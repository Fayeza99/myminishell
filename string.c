/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:03:06 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/26 10:20:41 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

t_string	new_string(char *s, int l)
{
	int			i;
	t_string	string;

	if (!s)
	{
		string.str = NULL;
		string.len = 0;
		return (string);
	}
	i = 0;
	string.len = l;
	string.str = (char *)malloc (l + 1);
	while (i < l)
	{
		string.str[i] = s[i];
		i++;
	}
	string.str[i] = '\0';
	return (string);
}
