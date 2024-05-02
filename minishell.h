/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:32 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/02 11:10:57 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <limits.h>
# include "include/libft/libft.h"
# include "mini_parse.h"

extern int	g_sig;

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
int			check_fd(char *filename);

//export
void		export2(char **args, t_mini *shell);
int			valid_export(char **args);
int			valid_var_name(char c, int index);
int			len_str_arr(char **s);

//path
int	file_check(char *s, char **env);
// int			file_check(char *s);
void		file_check1(char *command);
void		handle_no_permission(char *cmd);
void		handle_command_not_found(char *command);
char	*check_permissions(char *cmd, char **env);
// char		*check_permissions(char *cmd);
void		execute_builtin(t_mini *shell, t_cmd *cmd);

///exec
void		exec_without_pipe(t_mini *shell);
void		exec_helper(t_mini *shell, int **fd, int i, t_cmd *cmd);
void		multi_pipe(t_mini *shell);
void		wait_for_child_processes(t_mini *shell);
void		loop_through_commands(t_mini *shell, int **fd);
void		cleanup_multi_pipe(t_mini *shell);
void		initialize_multi_pipe(t_mini *shell);
void		forker(t_mini *shell, int i);
void		execute_command(t_mini *shell, t_cmd *cmd);
void		handle_fd_redirections(t_cmd *cmd);
void		close_file_descriptors(int **fd, int cmd_count);
void		redirect_std_io(int **fd, int i, t_mini *shell);
void		execute_external(t_mini *shell, t_cmd *cmd);
void		parent_process(pid_t pid, t_mini *shell);
void		child_process(t_cmd *cmd, int *fd, t_mini *shell);
pid_t		create_child(t_mini *shell, int i);
void		waiting(t_mini *shell);
void		close_pipes(t_mini *shell, int **pipes);
void		free_pipes(int **fd, int num_pipes);
void		piper(t_mini *shell, int **n, int j);
int			**malloc_pipes(t_mini *shell);
void		create_pipes(int **pipes, int num_pipes);
void		allocate_memory_for_pipes(int **pipes, int num_pipes);
int			count_cmd(t_mini *shell);

#endif