/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:32 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/26 11:53:42 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <limits.h>
# include "include/libft/libft.h"
# include "mini_parse.h"

extern int	g_sig;

typedef enum e_sig
{
	INTERACT = 1 << 0,
	S_INT = 1 << 1,
	S_TERM = 1 << 2,
	S_QUIT = 1 << 3,
}	t_sig;

void		leak(void);

int			read_command(t_mini *mini);
void		sig_init(void);
void		mini_handler(int sig);
void		configure_terminal(void);

// exec

int			ex_export(t_mini *shell, char **args);
char		*find_path(t_mini *shell, char *s);
int			ex_cd(char **args, t_mini *shell);
int			ex_echo(t_mini *shell, t_cmd *cmd);
int			ex_pwd(char **args);
int			ex_unset(t_mini *shell, t_cmd *cmd);
void		m_exec(t_mini *shell);
int			ft_exit(t_mini *shell, t_cmd *cmd);
int			valid_builtins(char *s);
int			count_cmd(t_mini *shell);
void		built_ins2(t_mini *shell, t_cmd *cmd);
// int		built_ins(t_mini *shell);

int			check_fd(t_mini *shell, char *filename);
int			file_check(t_mini *shell, char *s);


#endif