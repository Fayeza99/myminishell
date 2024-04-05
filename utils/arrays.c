/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:40:37 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/05 20:22:48 by fnikzad          ###   ########.fr       */
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

// adds a new string to an array, not malloced strings
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
	new[i++] = add;
	new[i] = NULL;
	free(s);
	return (new);
}

// adds a new string to an array, malloced strings
char	**ft_arr_realloc(char **s, char *add)
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
		new[i] = ft_strdup(s[i]);
		i++;
	}
	new[i++] = add;
	new[i] = NULL;
	ft_freearr(s);
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

// (frees s)
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

void	print_argv(char **s, t_type *type)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		printf("%s---%d\n", s[i], type[i]);
		i++;
	}
	printf("%s\n", s[i]);
}
