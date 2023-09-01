/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:40:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/01 16:27:11 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

void	init_parser(t_parser *tokens)
{
	tokens->redirect_list->file = NULL;
	tokens->cmd_list->cmd = NULL;
	tokens->cmd_list->strs = NULL;
	tokens->input = NULL;
	tokens->cmd_list = NULL;
	tokens->redirect_list = NULL;
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
	init_parser(new);
	new->input = input;
	new->next = NULL;
	return (new);
}

t_parser	*shelly_print_list(t_parser *token)
{
	t_parser	*list;

	list = token;
	while (list)
	{
		printf("lexer token list: [%s]\n", list->input);
		list = list->next;
	}
	return (token);
}
