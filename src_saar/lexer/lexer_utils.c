/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:40:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/31 18:50:25 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

t_parser	*lexer_listlast(t_parser *list)
{
	if (!list)
		mini_error("uhoh error, lstlast", errno);
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
		mini_error("malloc error listnew", errno);
	ft_bzero(new, sizeof(t_parser));
	new->input = input;
	new->hd_fd = -1;
	new->next = NULL;
	return (new);
}

t_parser	*shelly_print_list(t_parser *token)
{
	t_parser	*list;

	list = token;
	while (list)
	{
		printf("lexer list: [%s]\n", (char *)list->input);
		list = list->next;
	}
	return (token);
}
