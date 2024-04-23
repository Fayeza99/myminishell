/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:57:56 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/23 15:11:17 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		skip_arg(char *cmd, int i);
int		skip_redir(char *cmd, int i);
char	*next_arg(char *cmd, int *i);
void	split_argv(t_list *argv);

// create an argv list (no nullterminations)
t_list	*get_argv_lst(char *cmd)
{
	t_list	*argv;
	int		skip;
	char	*tmp;

	argv = NULL;
	if (!cmd || !*cmd || !valid_redir(cmd))
		return (NULL);
	while (*cmd)
	{
		skip = 0;
		tmp = next_arg(cmd, &skip);
		if (!tmp)
			return (ft_lst_delall(&argv, NULL), NULL);
		ft_lstadd_back(&argv, ft_lstnew((void *)tmp));
		cmd += skip;
	}
	return (argv);
}

int	skip_arg(char *cmd, int i)
{
	while (cmd[i] && !is_whitespace(cmd[i]))
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			i += skip_quote(&cmd[i]);
		if (cmd[i] == '>' || cmd[i] == '<')
			break ;
		i++;
	}
	return (i);
}

int	skip_redir(char *cmd, int i)
{
	i++;
	if (cmd[i] == '>' || cmd[i] == '<')
		i++;
	while (cmd[i] && is_whitespace(cmd[i]))
		i++;
	while (cmd[i] && !is_whitespace(cmd[i]))
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			i += skip_quote(&cmd[i]);
		else
			i++;
	}
	return (i);
}

// returns a pointer to the next arg, saves the next position in skip
char	*next_arg(char *cmd, int *i)
{
	char	*next;

	if (!cmd || !*cmd)
		return (NULL);
	while (cmd[*i] && is_whitespace(cmd[*i]))
		(*i)++;
	next = &cmd[*i];
	if (cmd[*i] == '>' || cmd[*i] == '<')
	{
		*i = skip_redir(cmd, *i);
		return (next);
	}
	while (cmd[*i] && !is_whitespace(cmd[*i]))
	{
		if (cmd[*i] == '\"' || cmd[*i] == '\'')
			*i += skip_quote(&cmd[*i]);
		else if (cmd[*i] == '>' || cmd[*i] == '<')
			break ;
		else
			(*i)++;
	}
	*i = skip_arg(cmd, *i);
	return (next);
}

// nullterminate the command string so the arguments are split
void	split_argv(t_list *argv)
{
	char	*str;
	int		skip;

	while (argv)
	{
		if (*(char *)(argv->content) == '>' || *(char *)(argv->content) == '<')
			skip = skip_redir(argv->content, 0);
		else
			skip = skip_arg(argv->content, 0);
		str = ft_substr(argv->content, 0, skip);
		argv->content = str;
		argv = argv->next;
	}
}
