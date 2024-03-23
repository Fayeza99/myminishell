/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:40:18 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/14 14:15:33 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*s3;

	i = 0;
	if (s1)
		i += ft_strlen(s1);
	if (s2)
		i += ft_strlen(s2);
	i++;
	s3 = malloc (sizeof(char) * i);
	if (s3 == 0)
		return (0);
	s3[0] = '\0';
	if (s1 && s1[0] != 0)
		ft_strlcat(s3, s1, i);
	if (s2 && s2[0] != 0)
		ft_strlcat(s3, s2, i);
	return (s3);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%s", ft_strjoin(NULL, NULL));
// }