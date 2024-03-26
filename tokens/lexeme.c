/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:58:31 by asemsey           #+#    #+#             */
/*   Updated: 2024/03/26 16:51:39 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer.h"

// malloc the lexeme_list (initialize)
t_list_lexeme	*create_list(void)
{
	t_list_lexeme	*list;

	list = (t_list_lexeme *)malloc(sizeof(t_list_lexeme));
	list->first = NULL;
	return (list);
}

// add a new item to lexeme_list
int	add_to_lex(t_list_lexeme *list, t_lexeme *lex)
{
	t_list	*node;

	if (!list->first)
		list->first = ft_lstnew(lex);
	else
	{
		node = list->first;
		while (node->next)
			node = node->next;
		node->next = ft_lstnew(lex);
	}
	return (1);
}

// free the lexeme_list
void	delete_list(t_list_lexeme *list)
{
	t_list		*prev;
	t_lexeme	*lexeme;

	while (list->first)
	{
		lexeme = list->first->content;
		free(lexeme->str.str);
		free(lexeme);
		prev = list->first;
		list->first = list->first->next;
		free(prev);
	}
	list->first = NULL;
}

// save an alphabetical string in lexeme_list as IDENTIFIER
int	identifier(t_list_lexeme *list, t_lexer *lexer)
{
	char	buffer[1000];
	int		i;

	i = 0;
	while (is_identifier(peekcharacter(lexer)))
	{
		buffer[i] = (char)getcharacter(lexer);
		i++;
	}
	buffer[i] = '\0';
	return (add_to_lex(list, create_lexeme(IDENTIFIERS, buffer, i)));
}
