/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:01:21 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/13 20:12:17 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*strf;
	size_t		i;

	if (s == 0 || f == 0)
		return (0);
	strf = malloc (sizeof(char) * (ft_strlen(s) + 1));
	if (strf == 0)
		return (0);
	i = 0;
	while (i < ft_strlen(s))
	{
		strf[i] = f(i, s[i]);
		i++;
	}
	strf[ft_strlen(s)] = '\0';
	return (strf);
}

// char	lower(unsigned int i, char c)
// {
// 	if (c >= 'A' && c <= 'Z')
// 		return (c - 'A' + 'a');
// 	return (c);
// }
// #include <stdio.h>
// int main() {
//     const char* input = "HELLO WORLD";
//     char* transformed = ft_strmapi(NULL, lower);
//     if (transformed != NULL) {
//         printf("Original: %s\n", input);
//         printf("Transformed: %s\n", transformed);
//         free(transformed);
//     } else {
//         printf("Memory allocation failed.\n");
//     }

//     return 0;
// }