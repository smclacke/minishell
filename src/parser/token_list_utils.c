/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 20:40:10 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/10 19:46:24 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

t_tokens	*token_listlast(t_tokens *list)
{
	if (!list)
	{
		printf("erroroororr\n");
		return (0);
	}
	if (list->next)
	{
		while (list->next)
			list = list->next;
	}
	return (list);
}

void	token_listadd_back(t_tokens **list, t_tokens *new)
{
	t_tokens	*last;

	if (*list)
	{
		last = token_listlast(*list);
		last->next = new;
	}
	else
		*list = new;
}

t_tokens	*token_listnew(char *input)
{
	t_tokens	*new;

	new = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new || !input)
	{
		// free(input);
		printf("erroroororr\n");
		return (0);
	}
	ft_bzero(new, sizeof(t_tokens));
	new->input = input;
	new->next = NULL;
	return (new);
}

int		count_tokens(char **tokens)
{
	int		count;

	count = ft_arrlen(tokens);
	return (count);
}
