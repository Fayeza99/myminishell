/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:32 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/31 19:06:57 by asemsey          ###   ########.fr       */
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
	t_list	*argv;
	int		fd_in;
	int		fd_out;
}	t_cmd;

typedef struct s_arg
{
	char	*arg;
	t_type	type;
}	t_arg;

t_mini		*mini_init(char **env);
int			mini_free(t_mini *mini);

t_cmd		*new_cmd(char *command);
t_list		*create_cmdlst(char **s);
void		ft_cmdprint(t_list *lst);
t_arg		*new_arg(char *arg);
t_list		*get_argv(char *cmd);
char		**get_argv_arr(char *cmd);
void		ft_argprint(t_list *lst);

int			open_quotes(char *str);
int			inside_quote(char *str, int pos);
int			open_pipe(char *str);
void		get_commands(t_mini *mini);
int			count_pipes(char *cmd);
int			valid_redir(char *str);

int			is_whitespace(char c);
int			ft_arrlen(char **s);
char		**ft_arr_add(char **s, char *add);
char		**ft_arrdup(char **s);
void		print_arr(char **cmd);
void		ft_freearr(char **s);
char		*ft_freejoin(char *s1, char *s2);

// test 0 test 0 test
//       ^      ^

// typedef enum e_tokens
// {
// 	IDENTIFIERS,
// 	LESS,
// 	GREATER,
// 	EXPANSION,
// 	PIPES,
// 	DASH,
// 	D_QUOTES,
// 	S_QUOTES,
// 	UNEXPECTED,
// 	END_OF_FILE,
// }	t_tokens;

#endif