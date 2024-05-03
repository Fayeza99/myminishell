/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:46:22 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/17 15:11:48 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	l;
	size_t	i;

	l = ft_strlen(s1);
	i = 0;
	dup = (char *) malloc (sizeof(char) * (l + 1));
	if (!dup)
		return (0);
	while (s1[i] != 0)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

// #include <stdio.h>
// int main() {
//     const char *original = "Hello, World!";
//     char *duplicate = ft_strdup(NULL);
// 	//char *duplicate = strdup(original);

//     if (duplicate != NULL) {
//         printf("Original: %s\n", original);
//         printf("Duplicate: %s\n", duplicate);

//         free(duplicate); // Don't forget to free the allocated memory
//     } else {
//         printf("Memory allocation failed.\n");
//     }
//     return 0;
// }