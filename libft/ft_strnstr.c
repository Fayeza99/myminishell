/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:43:17 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/17 20:02:49 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	if (*needle == 0)
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	if (len == 0)
		return (0);
	i = 0;
	if (*haystack && len >= needle_len)
	{
		while (i <= len - needle_len)
		{
			if (ft_strncmp(haystack + i, needle, needle_len) == 0)
				return ((char *)(haystack + i));
			i++;
		}
	}
	return (NULL);
}

// int main() {
//     const char* haystack = "";
//     const char* needle = "asd";
//     size_t max_len = ft_strlen(haystack);  // Maximum length to search

//     char* result = ft_strnstr(haystack, needle, 3);
// 	//char* result = strnstr(haystack, needle, 3);

//     if (result != NULL) {
//         printf("Substring found: %s\n", result);
//     } else {
//         printf("Substring not found.\n");
//     }

//     return 0;
// }