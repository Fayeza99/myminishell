/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:56:35 by fnikzad           #+#    #+#             */
/*   Updated: 2023/10/12 18:50:33 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s == 0 || f == 0)
		return ;
	while (s[i] != 0)
	{
		(f)(i, &s[i]);
		i++;
	}
}

// void	lower(unsigned int i, char *c)
// {
// 	if (*c >= 'A' && *c <= 'Z')
// 		*c = *c + 'a' - 'A';
// }
// #include <stdio.h>
// int main() {
//     char input[] = "HELLO WORLD";
// 	printf("BEFORE: %s\n", input);
//     ft_striteri(input, lower);
//     printf("Transformed: %s\n", input);

//     return 0;
// }