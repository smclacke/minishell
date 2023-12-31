/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 15:05:10 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/08 15:30:22 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_parser(t_parser *tokens)
{
	tokens->input = NULL;
	tokens->str = NULL;
	tokens->cmd = NULL;
	tokens->meta = NULL;
	tokens->abso = NULL;
	tokens->squote = NULL;
	tokens->dquote = NULL;
	tokens->here_doc = NULL;
}

t_parser		*lexer_listlast(t_parser *list)
{
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	return (list);
}

void	lexer_listadd_back(t_parser **list, t_parser *new)
{
	t_parser	*last;

	if (*list)
	{
		last = lexer_listlast(*list);
		last->next = new;
	}
	else
		*list = new;
}

t_parser	*lexer_listnew(void *input)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(*new));
	if (!new)
		return (0);
	new->input = input;
	new->next = NULL;
	return (new);
}

// print the tokens for testing purposes
t_parser	*shelly_print_list(t_parser *token)
{
	t_parser	*list;

	list = token;
	while (list)
	{
		printf("list: \t\t~: %s\n", list->input);
		list = list->next;
	}
	return (token);
}
