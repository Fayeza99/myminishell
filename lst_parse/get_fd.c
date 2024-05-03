/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:31:27 by asemsey           #+#    #+#             */
/*   Updated: 2024/05/02 16:41:33 by asemsey          ###   ########.fr       */
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
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(filename, 2);
			ft_putendl_fd(": is a directory", 2);
			exit(126);
		}
	}
	return (0);
}

void	write_heredoc(char *del, int *fd)
{
	char	*line;

	*fd = open(".heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return ;
		if (!ft_strcmp(line, del))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, *fd);
		free(line);
	}
	close(*fd);
	*fd = open(".heredoc", O_RDONLY);
}

int	get_fd(char *str, t_type type, int *fd_in, int *fd_out)
{
	if (!str || !*str)
		return (0);
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
		write_heredoc(str, fd_in);
	if (*fd_in == -1 || *fd_out == -1)
	{
		ft_putstr_fd("minishell: No such file or directory: ", 2);
		ft_putendl_fd(str, 2);
		return (0);
	}
	return (1);
}

void	remove_redir(t_cmd *cmd)
{
	int		i;
	t_list	*arg;

	i = 0;
	arg = cmd->args;
	while (arg)
	{
		if (cmd->type[i] != ARG)
			ft_lst_remove(&cmd->args, arg, free);
		arg = arg->next;
		i++;
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
			if (check_fd(file) || !get_fd((char *)file, cmd->type[i], \
				&cmd->fd_in, &cmd->fd_out))
				break ;
		}
		i++;
		arg = arg->next;
	}
	remove_redir(cmd);
}
