/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:40:37 by asemsey           #+#    #+#             */
/*   Updated: 2024/03/28 14:06:10 by asemsey          ###   ########.fr       */
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

void	print_arr(char **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd[i])
		printf("%s\n", cmd[i++]);
	printf("%s\n", cmd[i]);
}
