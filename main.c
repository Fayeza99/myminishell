/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:22:01 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/25 15:17:58 by fnikzad          ###   ########.fr       */
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
		list->first = ft_lstnew(lex);
	else
	{
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

void	quoted_str(t_list_lexeme *list, t_lexer *lexer)
{
	char	buffer[1000];
	int		i;
	
	i = 0;
	getcharacter(lexer);
	while ((is_identifier(peekcharacter(lexer)) || is_dash(peekcharacter(lexer)) || is_less(peekcharacter(lexer))
		|| is_greater(peekcharacter(lexer)) || is_expansion(peekcharacter(lexer))
		|| is_whitespace(peekcharacter(lexer)) || is_single_quotes(peekcharacter(lexer))
		|| is_pipes(peekcharacter(lexer))) && !(is_double_quotes(peekcharacter(lexer))))
	{
		buffer[i] = getcharacter(lexer);
		i++;
	}
	buffer[i] = '\0';
	if (is_double_quotes(peekcharacter(lexer)))
		getcharacter(lexer);
	add_to_lex(list, create_lexeme(D_QUOTES, buffer, i));
}

void	s_quoted_str(t_list_lexeme *list, t_lexer *lexer)
{
	char	buffer[1000];
	int		i;
	
	i = 0;
	getcharacter(lexer);
	while ((is_identifier(peekcharacter(lexer)) || is_dash(peekcharacter(lexer)) || is_less(peekcharacter(lexer))
		|| is_greater(peekcharacter(lexer)) || is_expansion(peekcharacter(lexer))
		|| is_whitespace(peekcharacter(lexer)) || is_double_quotes(peekcharacter(lexer))
		|| is_pipes(peekcharacter(lexer))) && !(is_single_quotes(peekcharacter(lexer))))
	{
		buffer[i] = getcharacter(lexer);
		i++;
	}
	buffer[i] = '\0';
	if (is_single_quotes(peekcharacter(lexer)))
		getcharacter(lexer);
	add_to_lex(list, create_lexeme(S_QUOTES, buffer, i));
}

void	lex(t_list_lexeme *list, t_lexer *lexer)
{
	char c;
	char u;

	while (peekcharacter(lexer))
	{
		if (is_whitespace(peekcharacter(lexer)))
		{
			getcharacter(lexer);
			continue;
		}
		else if (is_identifier(peekcharacter(lexer)))
			identifier(list, lexer);
		else if (is_less(peekcharacter(lexer)))
		{
			getcharacter(lexer);
			add_to_lex(list, create_lexeme(LESS, "<", 1));
		}
		else if (is_greater(peekcharacter(lexer)))
		{
			getcharacter(lexer);
			add_to_lex(list, create_lexeme(GREATER, ">", 1));
		}
		else if (is_dash(peekcharacter(lexer)))
		{
			getcharacter(lexer);
			add_to_lex(list, create_lexeme(DASH, "-", 1));
		}
		else if (is_pipes(peekcharacter(lexer)))
		{
			getcharacter(lexer);
			add_to_lex(list, create_lexeme(PIPES, "|", 1));
		}
		else if (is_expansion(peekcharacter(lexer)))
		{
			getcharacter(lexer);
			add_to_lex(list, create_lexeme(EXPANSION, "$", 1));
		}
		else if (is_double_quotes(peekcharacter(lexer)))
		{
			quoted_str(list, lexer);
		}
		else if (is_single_quotes(peekcharacter(lexer)))
		{
			s_quoted_str(list, lexer);
		}
		else
		{
			u = getcharacter(lexer);
			add_to_lex(list, create_lexeme(UNEXPECTED, &u, 1));
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
		add_history(s);
		lexer.current = s;
		lex(list, &lexer);
		t_list *node = list->first;
		while (node)
		{
			t_lexeme *lexeme = node->content;
			if (node->next != NULL)
			{
				printf("%s - ", get_token_name(lexeme->token));
				printf("%s - ", lexeme->str.str);
			}
			else
				printf("%s - %s \n", get_token_name(lexeme->token), lexeme->str.str);
			node = node->next;
		}
		free (s);
		delete_list(list);
	}
	clear_history();
	free(list);
}
