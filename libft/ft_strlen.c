/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:31:46 by fnikzad           #+#    #+#             */
/*   Updated: 2024/02/26 14:06:14 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s1)
{
	int	i;

	i = 0;
	while (s1 && s1[i])
		i++;
	return (i);
}

// #include <stdio.h>
// int main()
// {
// 	char s1[] = "abhdg";
// 	// printf("%lu", strlen(NULL));
// 	printf("%zu", ft_strlen(NULL));
// }