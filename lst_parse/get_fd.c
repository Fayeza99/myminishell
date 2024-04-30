/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:31:27 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/30 13:15:39 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_fd(char *filename)
{
	struct stat	file_stat;

	if (stat(filename, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			ft_putendl_fd(" is a directory", 2);
			exit(126);
		}
	}
	return (0);
}

void	write_heredoc(char *del, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			return ;
		}
		if (!ft_strcmp(line, del))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	get_fd(char *str, t_type type, int *fd_in, int *fd_out)
{
	if (!str || !*str)
		return ;
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
	if (type == HEREDOC)
	{
		*fd_in = open(".heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
		write_heredoc(str, *fd_in);
	}
}

void	set_cmd_fd(t_cmd *cmd)
{
	t_list	*arg;
	char	*file;
	int		i;

	arg = cmd->args;
	i = 0;
	while (arg)
	{
		if (cmd->type[i] != ARG)
		{
			file = arg->content + 1;
			if (cmd->type[i] == HEREDOC || cmd->type[i] == APPEND)
				file++;
			while (is_whitespace(*file))
				file++;
			if (check_fd(file))
				return ;
			get_fd((char *)file, cmd->type[i], \
				&cmd->fd_in, &cmd->fd_out);
			ft_lst_remove(&cmd->args, arg, free);
		}
		i++;
		arg = arg->next;
	}
}
