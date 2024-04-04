/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:32 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/04 13:22:48 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <limits.h>
# include "include/libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_type
{
	ARG,
	IN,
	OUT,
	HEREDOC,
	APPEND,
}	t_type;

typedef struct s_mini
{
	char	*command;
	char	**cmd_list;
	t_list	*current_cmd;
	int		exit_status;
	char	**env;
}	t_mini;

// commands are segments separated by pipes
typedef struct s_cmd
{
	char	*command;
	char	**argv;
	t_type	*type;
	// t_list	*args;
	int		fd_in;
	int		fd_out;
}	t_cmd;

// typedef struct s_arg
// {
// 	char	*arg;
// 	t_type	type;
// }	t_arg;

// parse

t_mini		*mini_init(char **env);
int			mini_free(t_mini *mini);
void		parse_input(t_mini *mini);

t_cmd		*new_cmd(char *command);
t_list		*create_cmdlst(char **s);
void		ft_cmdprint(t_list *lst);
char		**get_argv_arr(char *cmd);
t_type		*get_type_arr(char **argv);
void		print_argv(char **s, t_type *type);

int			open_quotes(char *str);
int			inside_quote(char *str, int pos);
int			open_pipe(char *str);
void		get_commands(t_mini *mini);
int			count_pipes(char *cmd);
int			valid_redir(char *str);

int			is_whitespace(char c);
char		*ft_freejoin(char *s1, char *s2);
int			ft_arrlen(char **s);
char		**ft_arr_add(char **s, char *add);
char		**ft_arr_realloc(char **s, char *add);
char		**ft_arrdup(char **s);
char		*ft_arrjoin(char **s);
void		print_arr(char **cmd);
void		ft_freearr(char **s);

char		*add_variables(char **env, char *str);
char		*ft_getenv(char *name, char **env, int freename);
char		*ft_expand(char *command, char **env);
char		*env_next(char *str, char **env, int *skip, int inquotes);
int			in_env(char *name, char **env, int free_name);

// exec

void		exec_cmd(t_mini *cmds);
int			ex_export(t_mini *shell, char **args);
void		pipes(t_mini *shell);
char		*find_path(char *s);


#endif