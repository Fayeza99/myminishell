/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:57:56 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/04 13:35:32 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_arg(char *cmd, int i)
{
	while (cmd[i] && !is_whitespace(cmd[i]))
	{
		if (cmd[i] == '>' || cmd[i] == '<')
			break;
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

// create an argv array (no nullterminations)
char	**get_argv_arr(char *cmd)
{
	char	**argv;
	int		skip;
	char	*tmp;

	// printf("getting argv...\n");
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

// skip spaces
// save pointer
// if redir:
// 		check second redir (++)
// 		skip spaces
// 		skip non-spaces
// 		set skip and return
// loop through non-spaces
// 		if redir set skip and return
// set skip and return

// > echo "hello">out
//   ^    ^      ^   
// > echo "hello" > out
//   ^    ^       ^    
// > echo "hello" >out
//   ^    ^       ^   
// > echo "hello"> out
//   ^    ^      ^    
// > echo>out "hello"
//   ^   ^    ^      
// > echo >out "hello"
//   ^    ^    ^      
// > >out echo "hello"
//   ^    ^    ^
// > > out echo "hello"
//   ^     ^    ^      