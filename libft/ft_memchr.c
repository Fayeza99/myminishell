/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 10:39:51 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/15 17:59:42 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ss;
	size_t			i;

	ss = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ss[i] == (unsigned char)c)
			return ((void *)(ss + i));
		i++;
	}
	return (0);
}

/*int main()
{
	
    unsigned char buffer[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    int value_to_find = 0x30;
    
    size_t buffer_size = sizeof(buffer);
    
    //void *result = memchr(buffer, value_to_find, buffer_size);
	void *result = ft_memchr(buffer, value_to_find, buffer_size);
    if (result != NULL) {
        printf("Value 0x%X found at position %ld\n", value_to_find, 
		(unsigned char *)result - buffer);
    } else {
        printf("Value 0x%X not found in the buffer.\n", value_to_find);
    }
    return 0;
}*/
