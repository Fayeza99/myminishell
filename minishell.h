/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:32 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/23 15:29:43 by fnikzad          ###   ########.fr       */
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

void	leak(void);

int		read_command(t_mini *mini);
void	mini_handler(int sig, siginfo_t *info, void *context);
void	disable_raw_mode(struct termios *original_termios);
void	enable_raw_mode(struct termios *original_termios);

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

#endif