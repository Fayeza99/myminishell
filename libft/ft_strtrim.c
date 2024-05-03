/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:16:24 by fnikzad           #+#    #+#             */
/*   Updated: 2024/02/20 15:10:02 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strim;
	int		start;
	int		end;
	int		strimlen;
	int		i;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *) s1);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] != 0 && ft_strchr(set, s1[start]) != 0)
		start++;
	while (end >= start && ft_strchr(set, s1[end]) != 0)
		end--;
	strimlen = end - start + 1;
	strim = malloc(sizeof(char) * (strimlen + 1));
	if (!strim)
		return (NULL);
	i = -1;
	while (++i <= strimlen)
		strim[i] = s1[start + i];
	strim[strimlen] = '\0';
	return (strim);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%s", ft_strtrim("lorem ipsum dolor sit amet", "tel"));
// }