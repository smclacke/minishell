/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 20:28:57 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/24 13:07:50 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo	errors
*/

int	is_pipe(void *input)
{
	if (ft_strcmp(input, PIPE) == 0)
		return (1);
	return (0);
}

int		count_procs(char **tokens)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (tokens[i])
	{
		if (is_pipe(tokens[i]))
			count++;
		i++;
	}
	return (count);
}

t_parser	*parser_listlast(t_parser *list)
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

void	parser_listadd_back(t_parser **list, t_parser *new)
{
	t_parser	*last;

	if (*list)
	{
		last = parser_listlast(*list);
		last->next = new;
	}
	else
		*list = new;
}

t_parser	*parser_listnew(t_procs *proc)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (!new || !proc)
	{
		free(proc);
		printf("erroroororr\n");
		return (0);
	}
	ft_bzero(new, sizeof(t_parser));
	new->proc = proc;
	new->hd_fd = -1;
	new->next = NULL;
	return (new);
}
