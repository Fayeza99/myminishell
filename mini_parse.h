/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:21:28 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/08 11:35:57 by asemsey          ###   ########.fr       */
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

typedef struct s_mini
{
	char	*command;
	char	**cmd_arr;
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

int			open_quotes(char *str);
int			inside_quote(char *str, int pos);
int			open_pipe(char *str);
int			count_pipes(char *cmd);
int			valid_redir(char *str);

// env

char		*ft_expand(t_mini *mini, char *command);
char		*add_variables(t_mini *mini, char *str);
char		*env_next(t_mini *mini, char *str, int *skip, int inquotes);
char		*ft_getenv(char *name, char **env, int freename);
int			in_env(char *name, char **env, int free_name);

// argv

char		**get_argv_arr(char *cmd);
void		split_argv(char **argv);
char		*remove_quotes(char *str);
char		**finalize_argv(char **old);
t_type		*get_type_arr(char **argv);

// utils

int			is_whitespace(char c);
char		*ft_freejoin(char *s1, char *s2);
int			ft_arrlen(char **s);
char		**ft_arr_add(char **s, char *add);
char		**ft_arr_realloc(char **s, char *add);
char		**ft_arrdup(char **s);
char		*ft_arrjoin(char **s);
void		ft_freearr(char **s);
void		print_arr(char **cmd);

void		display_struct(t_mini *mini);

#endif