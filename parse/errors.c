/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:13:02 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/15 13:27:21 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_err
{
	S_QUOTE = 1,
	D_QUOTE = 2,
	REDIR = 4,
	PIPE = 8,
}	t_err;

int	valid_input(char *str)
{
	int	flags;

	flags = 0;
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str == '\'' && !(flags & S_QUOTE))
			flags |= S_QUOTE;
		
		str++;
	}
	str--;
	if (flags)
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		return (0);
	}
}
