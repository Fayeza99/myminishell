/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:31:27 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/25 11:33:01 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_fd(t_mini *shell, char *filename)
{
	struct stat file_stat;
	
	// if (access(filename, F_OK) == -1) {
    //     // File doesn't exist
    //     return 0;
    // }

    // Check execute permission
    // if (access(filename, X_OK) == -1) {
    //     // Execute permission denied
	// 	shell->exit_status = 126;
    //     return 1;
    // }
    if (stat(filename, &file_stat) == 0)
	{

		if (S_ISDIR(file_stat.st_mode))
		{
			// It's a directory
			shell->exit_status = 126;
			return 1;
		}
		else
		{
			// It's not a directory
			return 0;
		}
	}
	return (0);
}

void	write_heredoc(char *del, int fd)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		line = readline(NULL);
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

void	set_cmd_fd(t_mini *shell, t_cmd *cmd)
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
			if (check_fd(shell, file))
				return ;
			get_fd((char *)file, cmd->type[i], \
				&cmd->fd_in, &cmd->fd_out);
			ft_lst_remove(&cmd->args, arg, free);
		}
		i++;
		arg = arg->next;
	}
}
