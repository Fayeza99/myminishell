/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:23:22 by fnikzad           #+#    #+#             */
/*   Updated: 2024/02/20 14:47:13 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if (d == s || len == 0)
		return (d);
	if (d < s)
	{
		ft_memcpy(d, s, len);
	}
	else if (d > s)
	{
		while (len > 0)
		{
			len--;
			d[len] = s[len];
		}
	}
	return (d);
}

// #include<stdio.h>
// int main()
// {
// 	char src[] = "hello";
// 	char *dst = src + 2;
// 	printf("BEFORE: %s\n", dst);
// 	// printf("test\n");
// 	// memmove(dst, src, ft_strlen(src) + 1);
// 	ft_memmove(dst, src, ft_strlen(src) + 1);
// 	printf("SRC:%s\n", src);
// 	printf("AFTER:%s\n", dst);
// }
