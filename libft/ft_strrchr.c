/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 10:28:05 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/17 19:19:56 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)

{
	int	i;

	i = 0;
	c = (char) c;
	while (s[i] != 0)
		i++;
	while (i >= 0)
	{
		if (s[i] == c)
		{
			return (&((char *)s)[i]);
		}
		i--;
	}
	return (0);
}

// int main()
// {
// 	const char *s = "ddfff";
// 	int c = 'd';
// 	//char *r = strrchr(s, c);
// 	char *r = ft_strrchr(s, c);
// 	printf("'%c' is at %ld", c, r - s);
// }
