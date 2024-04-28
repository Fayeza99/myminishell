/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:44:48 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/28 15:12:59 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long	ft_atol(const char *s)
{
	long	num;
	int		sign;
	int		i;

	sign = 1;
	i = 0;
	num = 0;
	while (s[i] && is_whitespace(s[i]))
		i++;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (s[i] == '+')
	{
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		num = num * 10 + (s[i] - '0');
		i++;
	}
	return (num * sign);
}

int	arr_len(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_exit(t_mini *shell, t_cmd *cmd)
{
	shell->exit_status = 0;
	if (arr_len(cmd->argv) > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		shell->exit_status = 1;
		return (1);
	}
	if (arr_len(cmd->argv) == 2)
	{
		shell->exit_status = ft_atol(cmd->argv[1]);
		if (shell->exit_status == INT_MAX
			|| shell->exit_status == INT_MIN
			|| shell->exit_status == 0)
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			shell->exit_status = 255;
		}
	}
	if (!count_cmd(shell))
		printf("exit\n");
	exit(shell->exit_status);
}
