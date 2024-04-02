/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:32 by fnikzad           #+#    #+#             */
/*   Updated: 2024/04/02 12:39:46 by fnikzad          ###   ########.fr       */
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

typedef enum e_tokens
{
	IDENTIFIERS,
	LESS,
	GREATER,
	EXPANSION,
	PIPES,
	DASH,
	D_QUOTES,
	S_QUOTES,
	UNEXPECTED,
	END_OF_FILE,
}	t_tokens;

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
	char			*command;
	char			**argv;
	int				fd_in;
	int				fd_out;
}	t_cmd;

t_mini		*mini_init(char **env);
int			mini_free(t_mini *mini);
t_cmd		*new_cmd(char *command);
t_list		*create_cmdlst(char **s);
void		ft_lstprint(t_list *lst);

int			open_quotes(char *str);
int			inside_quote(char *str, int pos);
int			open_pipe(char *str);
void		get_commands(t_mini *mini);
int			get_argc(char *cmd);
int			count_pipes(char *cmd);

int			is_whitespace(char c);
int			ft_arrlen(char **s);
char		**ft_arrdup(char **s);
void		print_arr(char **cmd);
void		ft_freearr(char **s);
char		*ft_freejoin(char *s1, char *s2);

// test 0 test 0 test
//       ^      ^

// commands are segments separated by pipes
// typedef struct s_cmd
// {
// 	// char			*command;
// 	char			**argv;
// 	// int				argc;
// 	// int				fd_out;
// 	char			**files_to_create;
// 	struct s_cmd	*next_cmd;
// }	t_cmd;


void	exec_cmd(t_mini *cmds);
int		ex_export(t_mini *shell, char **args);



#endif