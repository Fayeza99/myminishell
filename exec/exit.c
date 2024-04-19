/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:44:48 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/19 14:30:20 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long	ft_atol(const char *s)
{
	long num = 0;
	int	sign = 1;
	int i = 0;
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

int		arr_len(char **s)
{
	int i = 0;
	while(s && s[i])
		i++;
	return (i);
}

int	ft_exit(t_mini *shell)
{
	t_cmd *cmd = shell->current_cmd->content;
	shell->exit_status = 0;
	int	valid = 0;
	if (arr_len(cmd->argv) > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	if (arr_len(cmd->argv) == 2)
	{
		shell->exit_status = ft_atol(cmd->argv[1]);
		if (shell->exit_status == LLONG_MAX || shell->exit_status == LLONG_MIN)
		{
			ft_putendl_fd("exit: numeric argument required", 2);
		}
		else
		{
			valid = 1;
		}
	}
	printf("exit\n");
	if (valid)
		exit(shell->exit_status);
	else
		exit(EXIT_SUCCESS);
}