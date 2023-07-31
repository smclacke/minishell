/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:40:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/31 21:31:30 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/sarah.h"

// lexer list func
t_lexer		*lexer_listlast(t_lexer *list)
{
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	return (list);
}

// lexer list func
void	lexer_listadd_back(t_lexer **list, t_lexer *new)
{
	t_lexer	*last;

	if (*list)
	{
		last = lexer_listlast(*list);
		last->next = new;
	}
	else
		*list = new;
}

// lexer list func
t_lexer	*lexer_listnew(void *input)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(*new));
	if (!new)
		return (0);
	new->input = input;
	new->next = 0;
	return (new);
}

// print lexer tokens
t_lexer	*print_lexer(t_lexer *token)
{
	t_lexer	*list;

	list = token;
	while (list)
	{
		printf("lexer: \t\t~: %s\n", list->input);
		list = list->next;
	}
	return (token);
}
