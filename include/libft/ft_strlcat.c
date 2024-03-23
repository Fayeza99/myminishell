/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:22:25 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/16 18:50:40 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	i = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dstsize == 0)
		return (slen);
	if (dstsize <= dlen)
		slen += dstsize;
	else
		slen += dlen;
	while (src[i] != 0 && dlen + 1 < dstsize)
	{
		dst[dlen++] = src[i++];
	}
	dst[dlen] = 0;
	return (slen);
}

// int main()
// {
// 	char d[7] = "hello";
// 	char s[10] = "e";
// 	//size_t cnct = strlcat(d, s, 0);
// 	size_t cnct = ft_strlcat(d, s, 0);
// 	printf("cnct : %zu\n", cnct);
// 	printf("dst : %s", d);
// }