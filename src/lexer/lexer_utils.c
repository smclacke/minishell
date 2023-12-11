/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 15:40:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/11 16:42:59 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo errors norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/

t_lexer	*lexer_listlast(t_lexer *list)
{
	if (!list)
	{
		free(list);
		// mini_error("general: lstlast()", E_GENERAL);
		return (0);
	}
	if (list->next)
	{
		while (list->next)
			list = list->next;
	}
	return (list);
}

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

/**
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
t_lexer	*lexer_listnew(char *input)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new || !input)
		// mini_error("malloc error: listnew()", E_MALLOC);
		return (0);
	ft_bzero(new, sizeof(t_lexer));
	new->input = input;
	// new->hd_fd = -1; // move this somewhere where process struct is inited
	new->next = NULL;
	return (new);
}
