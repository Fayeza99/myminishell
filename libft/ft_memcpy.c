/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:45:13 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/11 11:04:47 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	s = src;
	d = dst;
	i = 0;
	if (d == s || n == 0)
		return (d);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

// int main()
// {
// 	const char src[0];
// 	char dst[0];
// 	memcpy(dst, src, strlen(src) + 1);
// 	//ft_memcpy(dst, src, strlen(src) + 1);
// 	printf("%s", src);
// }