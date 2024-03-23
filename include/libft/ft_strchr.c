/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 20:03:08 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/17 19:18:09 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	c = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&((char *)s)[i]);
		i++;
	}
	if (c == 0)
		return ((&((char *)s)[i]));
	return (NULL);
}

// int main()
// {
// 	const char s[] = "hello";
// 	int c = 0;
// 	//char *r = strchr(s, c);
// 	char *r = ft_strchr(s, c);
// 	printf("'%c' is at %ld", c, r - s);
// }