/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:55:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/05 18:04:48 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	expand_quotes(t_parser *tokens)
{
	t_parser	*list;

	list = tokens;
	while (list)
	{
		if (list->cmd)
		{
			if (check_quotes(list->cmd))
			{
				if (!check_space(list->cmd))
					list->cmd = remove_quotes(list->cmd);	
			}
		}
		if (list->str)
		{
			if (check_quotes(list->str))
				list->str = remove_quotes(list->str);
		}
		list = list->next;
	}
}
