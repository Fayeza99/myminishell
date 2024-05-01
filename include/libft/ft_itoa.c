/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:59:28 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/01 13:48:00 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		return (1);
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static	char	*min(void)
{
	char	*str;

	str = malloc (sizeof(char) * 12);
	ft_strlcpy(str, "-2147483648", 12);
	return (str);
}

char	*ft_itoa(int n)
{
	int		neg;
	char	*str;
	int		i;

	neg = 0;
	if (n == -2147483648)
		return (min());
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	str = malloc (sizeof(char) * (count(n) + neg + 1));
	if (str == 0)
		return (0);
	if (neg)
		str[0] = '-';
	i = neg + count(n);
	str[i--] = '\0';
	while (i >= neg)
	{
		str[i--] = '0' + (n % 10);
		n = n / 10;
	}
	return (str);
}

// #include <stdio.h>
// int main()
// {
// 	int n = -21483648;
// 	printf("%d\n", count(n));
// 	printf("%s", ft_itoa(n));
// }
