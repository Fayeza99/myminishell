/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:01 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/26 13:42:42 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens/lexer.h"

int	main()
{
	t_list_lexeme	*list;
	t_lexer			lexer;
	t_list			*node;
	t_lexeme		*lexeme;
	char			*s;

	list = create_list();
	while (1)
	{
		s = readline("minishell> ");
		add_history(s);
		lexer.current = s;
		add_tokens(list, &lexer);
		node = list->first;
		while (node)
		{
			lexeme = node->content;
			if (node->next != NULL)
			{
				printf("%s - ", get_token_name(lexeme->token));
				printf("%s - ", lexeme->str.str);
			}
			else
				printf("%s - %s \n", get_token_name(lexeme->token), lexeme->str.str);
			node = node->next;
		}
		free(s);
		delete_list(list);
	}
	clear_history();
	free(list);
}
