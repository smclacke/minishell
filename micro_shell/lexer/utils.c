/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 15:05:10 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/25 15:14:38 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// t_lexer version
t_lexer		*micro_lexer_listlast(t_lexer *list)
{
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	return (list);
}

// t_lexer version
void	micro_lexer_listadd_back(t_lexer **list, t_lexer *new)
{
	t_lexer	*last;

	if (*list)
	{
		last = micro_lexer_listlast(*list);
		last->next = new;
	}
	else
		*list = new;
}

// t_lexer version
t_lexer	*micro_lexer_listnew(void *input)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(*new));
	if (!new)
		return (0);
	new->input = input;
	new->next = 0;
	return (new);
}

// print tokens
t_lexer	*micro_ft_print_tokens(t_lexer *token)
{
	t_lexer	*list;
	
	list = token;
	while (list)
	{
		printf("token: %s\n", list->input);
		list = list->next;
	}
	return (token);
}
