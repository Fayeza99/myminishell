/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:01 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/23 17:44:16 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_list_lexeme *create_list()
{
	t_list_lexeme *list;

	list = (t_list_lexeme *)malloc(sizeof(t_list_lexeme));
	list->first = NULL;
	return (list);	
}

void	add_to_lex(t_list_lexeme *list, t_lexeme *lex)
{
	t_list *node;
	if (!list->first)
	{
		list->first = ft_lstnew(lex);
	}
	else {
		node = list->first;
		while (node->next)
			node = node->next;
		node->next = ft_lstnew(lex);
	}
}

void	delete_list(t_list_lexeme *list)
{
	while (list->first)
	{
		t_list *prev;
		t_lexeme *lexeme;
		lexeme = list->first->content;
		free(lexeme->str.str);
		free(lexeme);
		prev = list->first;
		list->first = list->first->next;
		free(prev);
	}
	list->first = NULL;
}

void	identifier(t_list_lexeme *list, t_lexer *lexer)
{
	char buffer[1000];

	int i = 0;
	while (is_identifier(peekcharacter(lexer)))
	{
		buffer[i] = getcharacter(lexer);
		i++;
	}
	buffer[i] = '\0';
	add_to_lex(list, create_lexeme(IDENTIFIERS, buffer, i));
}

void	lex(t_list_lexeme *list, t_lexer *lexer)
{
	char c;

	while (peekcharacter(lexer))
	{
		if (is_whitespace(peekcharacter(lexer))) {
			getcharacter(lexer);
			continue;
		}
		else if (is_identifier(peekcharacter(lexer)))
			identifier(list, lexer);
		else if (is_less(peekcharacter(lexer))) {
			getcharacter(lexer);
			add_to_lex(list, create_lexeme(LESS, "<", 1));
		}
		else if (is_greater(peekcharacter(lexer))) {
			getcharacter(lexer);
			add_to_lex(list, create_lexeme(GREATER, ">", 1));
		}
		else if (is_dash(peekcharacter(lexer))) {
			getcharacter(lexer);
			add_to_lex(list, create_lexeme(DASH, "-", 1));
		}
		else if (is_pipes(peekcharacter(lexer))) {
			getcharacter(lexer);
			add_to_lex(list, create_lexeme(PIPES, "|", 1));
		}
		else if (is_expansion(peekcharacter(lexer))) {
			getcharacter(lexer);
			add_to_lex(list, create_lexeme(EXPANSION, "$", 1));
		}
		else {
			getcharacter(lexer);
			add_to_lex(list, create_lexeme(UNEXPECTED, "EOF", 3));
		}
	}
	add_to_lex(list, create_lexeme(END_OF_FILE, &c, 1));
}

int	main()
{
	t_list_lexeme	*list;
	t_lexer			lexer;
	char *s;

	list = create_list();
	
	while (1)
	{
		s = readline("minishell> ");
		lexer.current = s;
		lex(list, &lexer);
		t_list *node = list->first;
		while (node) {
		    t_lexeme *lexeme = node->content;
		    if (node->next != NULL)
		       printf("%s - ", get_token_name(lexeme->token));
		    else
		       printf("%s - %s \n", get_token_name(lexeme->token), lexeme->str.str);
		    node = node->next;
		}
		free (s);
		delete_list(list);
		
	}
	free(list);
}
