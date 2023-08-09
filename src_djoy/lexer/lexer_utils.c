/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:40:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/08 22:07:31 by djoyke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

void	init_parser(t_parser *tokens)
{
	// tokens->input = NULL;
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
	int 		i;

	list = token;
	i = 0;
	while (list)
	{
		printf("iterations [%i]\n", i);
		// printf("list: \t\t~: %s\n", list->input);
		i++;
		list = list->next;
	}
	return (token);
}