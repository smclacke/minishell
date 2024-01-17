/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   proc_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 16:20:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/17 17:28:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int		proc_redir(char *input)
{
	if (ft_strcmp(input, MOREMORE) == 0)
		return (1);
	else if (ft_strcmp(input, LESSLESS) == 0)
		return (2);
	else if (ft_strcmp(input, MORE) == 0)
		return (3);
	else if (ft_strcmp(input, LESS) == 0)
		return (4);
	return (0);
}

t_procs	*proc_listlast(t_procs *list)
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

void	proc_listadd_back(t_procs **list, t_procs *new)
{
	t_procs	*last;

	if (*list)
	{
		last = proc_listlast(*list);
		last->next = new;
	}
	else
		*list = new;
}

t_procs	*proc_listnew(void *proc_arr)
{
	t_procs	*new;

	new = (t_procs *)malloc(sizeof(t_procs));
	if (!new || !proc_arr)
	{
		free(proc_arr);
		printf("erroroororr\n");
		return (0);
	}
	ft_bzero(new, sizeof(t_procs));
	new->input = proc_arr;
	new->next = NULL;
	return (new);
}
