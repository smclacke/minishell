/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:40:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/01 17:56:53 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo errors
*/

t_parser	*lexer_listlast(t_parser *list)
{
	if (!list)
	{
		free(list);
		mini_error("uhoh error, lstlast", errno);
	}
	if (list->next)
	{
		while (list->next)
			list = list->next;
	}
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

	new = (t_parser *)malloc(sizeof(t_parser));
	if (!new || !input)
	{
		free(input);
		mini_error("malloc error listnew", errno);
	}
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
	// printf("")
	while (list)
	{
		printf("lexer list: [%s]\n", (char *)list->input);
		list = list->next;
	}
	return (token);
}
