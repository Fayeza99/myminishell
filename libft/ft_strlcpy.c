/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:10:37 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/11 12:40:20 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;
	size_t	i;

	slen = 0;
	while (src[slen] != 0)
	{
		slen++;
	}
	if (dstsize == 0 || dst == 0)
		return (slen);
	i = 0;
	while (i < (dstsize - 1) && src[i] != 0)
	{
		dst [i] = src [i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}

// int main()
// {
//     char s[] = "hello";
// 	char d[5];

// 	//size_t n = strlcpy(d, s, sizeof(d));
// 	size_t n = ft_strlcpy(d, s, sizeof(d));
// 	printf("n = %zu\n", n);
// 	printf("d = %s", d);
// }
