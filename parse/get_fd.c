/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:31:27 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/20 12:49:18 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_fd(char *str, t_type type, int *fd_in, int *fd_out)
{
	if (!str || !*str)
		return ;
	if (type == HEREDOC || type == APPEND)
		str += 2;
	else
		str++;
	while (is_whitespace(*str))
		str++;
	if ((type == OUT || type == APPEND) && *fd_out != STDOUT_FILENO)
		close(*fd_out);
	if (type == OUT)
		*fd_out = open(str, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (type == APPEND)
		*fd_out = open(str, O_RDWR | O_APPEND | O_CREAT, 0644);
	if ((type == IN || type == HEREDOC) && *fd_in != STDIN_FILENO)
		close(*fd_in);
	if (type == IN)
		*fd_in = open(str, O_RDONLY);
}


void	set_cmd_fd(t_cmd *cmd)
{
	t_list	*arg;
	int		i;

	arg = cmd->args;
	i = 0;
	while (arg)
	{
		if (cmd->type[i] != ARG && cmd->type[i] != HEREDOC)
		{
			get_fd((char *)arg->content, cmd->type[i], \
				&cmd->fd_in, &cmd->fd_out);
			ft_lst_remove(&cmd->args, arg, NULL);
		}
		i++;
		arg = arg->next;
	}
}
