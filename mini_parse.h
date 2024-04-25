/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:21:28 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/24 17:49:25 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PARSE_H
# define MINI_PARSE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "include/libft/libft.h"

typedef enum e_type
{
	ARG,
	IN,
	OUT,
	HEREDOC,
	APPEND,
}	t_type;

typedef enum e_err
{
	S_QUOTE = 1 << 0,
	D_QUOTE = 1 << 1,
	PIPE = 1 << 2,
	DPIPE = 1 << 3,
	REDIR = 1 << 4,
}	t_err;

typedef struct s_mini
{
	char	*command;
	t_list	*current_cmd;
	int		exit_status;
	int		flag;
	int		*pids;
	char	**env;
}	t_mini;

// commands are segments separated by pipes
typedef struct s_cmd
{
	char	*command;
	t_list	*args;
	char	**argv;
	t_type	*type;
	int		fd_in;
	int		fd_out;
}	t_cmd;

// structs

t_mini		*mini_init(void);
int			mini_free(t_mini *mini);
int			micro_free(t_mini *mini);
void		parse_input(t_mini *mini);
void		get_commands(t_mini *mini);
t_cmd		*new_cmd(char *command);
t_list		*create_cmdlst(char **s);

// errors

int			get_flag(char *str);
int			is_token(char c);
int			inside_quote(char *str, int pos);
int			count_pipes(char *cmd);
int			valid_redir(char *str);
int			ft_error(int flag, char *str);

// env

char		*ft_expand(t_mini *mini, char *command);
char		*add_variables(t_mini *mini, char *str);
char		*env_next(t_mini *mini, char *str, int *skip, int inquotes);
char		*ft_getenv(char *name, char **env, int freename);
int			in_env(char *name, char **env, int free_name);
int			env_validchar(char c, int index);

// argv

void		nullterminate_cmd(t_list *lst);
void		set_cmd_fd(t_mini *shell, t_cmd *cmd);
t_list		*get_argv_lst(char *cmd);
void		split_argv(t_list *argv);
t_type		*get_type_arr(t_list *argv);
void		unquote_argv(t_list **argv);

// utils

void		ft_lst_remove(t_list **lst, t_list *rem, void (*del)(void *));
char		**ft_lst_toarr(t_list *lst);
void		ft_lst_delall(t_list **lst, void (*del)(void *));
int			is_whitespace(char c);
char		*ft_freejoin(char *s1, char *s2);
int			ft_arrlen(char **s);
char		**ft_arr_add(char **s, char *add);
char		**ft_arr_realloc(char **s, char *add);
char		**ft_arrdup(char **s);
char		*ft_arrjoin(char **s);
void		ft_freearr(char **s);

void		print_arr(char **cmd);
void		ft_lstprint(t_list *lst);
void		ft_cmdprint(t_list *lst);
void		display_struct(t_mini *mini);

#endif