/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:41:42 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/11 12:41:01 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (n-- > 0)
	{
		if (*ss1 != *ss2)
			return (*ss1 - *ss2);
		ss1++;
		ss2++;
	}
	return (0);
}

/*int main() {
    char str1[] = "teste";
    char str2[] = "testex";
    int result;

    // Compare the first 5 characters of str1 and str2
    //result = memcmp(str1, str2, 6);
	result = ft_memcmp(str1, str2, 5);

    if (result == 0) {
        printf("The first 5 characters are identical.\n");
    } else if (result < 0) {
        printf("The first differing character in str1 is less than the 
		corresponding character in str2.\n");
    } else {
        printf("The first differing character in str1 is greater than the 
		corresponding character in str2.\n");
    }

    return 0;
}*/
