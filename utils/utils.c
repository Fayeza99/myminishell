/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:52:01 by asemsey           #+#    #+#             */
/*   Updated: 2024/05/01 15:40:37 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	return ((c >= 9 && c < 14) || c == 32);
}

int	ft_arrlen(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_freejoin(char *s1, char *s2)
{
	int		i;
	char	*s3;

	i = 1;
	if (s1)
		i += ft_strlen(s1);
	if (s2)
		i += ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * i);
	if (s3 == 0)
		return (0);
	s3[0] = '\0';
	if (s1 && s1[0] != 0)
		ft_strlcat(s3, s1, i);
	if (s2 && s2[0] != 0)
		ft_strlcat(s3, s2, i);
	free(s1);
	return (s3);
}

// (frees s) turns an array of strings into one str
char	*ft_arrjoin(char **s)
{
	char	*new;
	int		i;

	if (!s || !s[0])
		return (NULL);
	i = 0;
	new = NULL;
	while (s[i])
		new = ft_freejoin(new, s[i++]);
	ft_freearr(s);
	return (new);
}
