/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:57:56 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/08 11:14:57 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		skip_arg(char *cmd, int i);
int		skip_redir(char *cmd, int i);
char	*next_arg(char *cmd, int *i);
void	split_argv(char **argv);

// create an argv array (no nullterminations)
char	**get_argv_arr(char *cmd)
{
	char	**argv;
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
			return (free(argv), NULL);
		argv = ft_arr_add(argv, tmp);
		cmd += skip;
	}
	return (argv);
}

int	skip_arg(char *cmd, int i)
{
	while (cmd[i] && !is_whitespace(cmd[i]))
	{
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
		i++;
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
	if (cmd[*i] == '\"' || cmd[*i] == '\'')
		*i += skip_quote(&cmd[*i]);
	*i = skip_arg(cmd, *i);
	return (next);
}

// nullterminate the command string so the arguments are split
void	split_argv(char **argv)
{
	int		i;
	char	*str;

	i = 0;
	while (argv[i] && argv[i + 1])
	{
		str = argv[i + 1] - 1;
		while (is_whitespace(*str))
			str--;
		str++;
		*str = '\0';
		i++;
	}
}
