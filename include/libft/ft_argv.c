/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:26:45 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/31 12:42:11 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// !!! undefined behaviour for unclosed quotes !!!

int	skip_quote(char *str)
{
	int		i;
	char	c;

	i = 1;
	c = *str;
	while (str && str[i] && str[i] != c)
		i++;
	i++;
	return (i);
}

static int	count(const char *str)
{
	int	words;

	words = 0;
	while (str && *str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str && !ft_isspace(*str))
			words++;
		while (*str)
		{
			if (*str && (*str == '\"' || *str == '\''))
			{
				str += skip_quote((char *)str);
				continue ;
			}
			if (*str && ft_isspace(*str))
				break ;
			str++;
		}
	}
	return (words);
}

static char	*ft_copy(const char *str, int *len)
{
	int		v[2];
	char	*s;

	v[0] = 0;
	while (str && str[v[0]])
	{
		if (str[v[0]] && (str[v[0]] == '\"' || str[v[0]] == '\''))
		{
			v[0] += skip_quote((char *)&str[v[0]]);
			continue ;
		}
		if (str[v[0]] && ft_isspace(str[v[0]]))
			break ;
		v[0]++;
	}
	s = (char *)malloc(sizeof(char) * (v[0] + 1));
	if (!s)
		return (NULL);
	v[1] = 0;
	while (str && *str && v[1] < v[0])
		s[v[1]++] = *str++;
	s[v[1]] = '\0';
	*len = v[1];
	return (s);
}

char	**ft_argv(const char *str)
{
	char	**strs;
	int		v[3];

	(void)str;
	v[0] = count(str);
	strs = (char **)malloc(sizeof(char *) * (v[0] + 1));
	if (!strs)
		return (NULL);
	v[1] = 0;
	while (v[1] < v[0])
	{
		while (str && *str && ft_isspace(*str))
			str++;
		strs[v[1]++] = ft_copy(str, &v[2]);
		if (!strs[v[1] - 1])
			return ((char **)free_all(strs));
		str += v[2];
	}
	strs[v[1]] = NULL;
	return (strs);
	return (NULL);
}

// #include <stdio.h>
// int main()
// {
// 	int i = 0;
// 	const char *input = "echo hello>test";

// 	// printf("-%d-\n", count(input));
// 	printf("string:   %s\n", input);
// 	char **result = ft_argv(input);
// 	while (result && result[i])
// 		printf("%s\n", result[i++]);
// }
