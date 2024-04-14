/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:26:05 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/14 16:50:36 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char *s)
{
	char	**all_path;
	char	*cmd;
	int		i;
	char	*tmp;

	all_path = ft_split(getenv("PATH"), ':');
	i = 0;
	tmp = ft_strjoin("/", s);
	while (all_path[i])
	{
		cmd = ft_strjoin(all_path[i++], tmp);
		if (access(cmd, X_OK) == 0)
			break;
		free(cmd);
	}
	free(tmp);
	ft_freearr(all_path);
	return (cmd);
}
