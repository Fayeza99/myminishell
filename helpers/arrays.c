/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:40:37 by asemsey           #+#    #+#             */
/*   Updated: 2024/03/31 12:18:58 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_arrlen(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

// no malloced strings!!! just pointer
char	**ft_arr_add(char **s, char *add)
{
	char	**new;
	int		i;

	if (!add)
		return (s);
	new = (char **)malloc(sizeof(char *) * (ft_arrlen(s) + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		new[i] = s[i];
		i++;
	}
	// printf("%d\n", i);
	new[i++] = add;
	new[i] = NULL;
	free(s);
	return (new);
}

char	**ft_arrdup(char **s)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * ft_arrlen(s) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		new[i] = ft_strdup(s[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	ft_freearr(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		free(s[i++]);
	free(s);
}

void	print_arr(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		printf("%s\n", s[i++]);
	printf("%s\n", s[i]);
}
