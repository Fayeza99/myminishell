/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:10:13 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/15 19:58:49 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	t;
	void	*memory;

	t = count * size;
	if (count != 0 && size != 0 && t / size != count)
		return (0);
	memory = malloc(t);
	if (memory != 0)
		ft_bzero(memory, (size_t)t);
	return (memory);
}

// #include <stdio.h>
// int main()
// {
// 	int *mem;
// 	size_t count = 214748323648;
// 	size_t size = sizeof(int);
// 	size_t i = 0;
// 	mem = ft_calloc(count, size);
// 	//mem = calloc(count, size);
// 	if (mem != 0)
// 	{
// 		while (i < count)
// 		{
// 			printf("%d", mem[i]);
// 			i++;
// 		}
// 		free(mem);
// 	}
// }