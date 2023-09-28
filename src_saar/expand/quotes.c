/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:55:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/28 23:33:21 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @brief	removes both single and double quotes from in and around cmds
 * 			checks if there are spaces within the quotations 
 * 			(i.e. cmd + str/flag), if so, leaves the quotes since the
 * 			cmd is invalid
 * @param	tokens from parser
 * @return	expanded tokens
*/
t_parser	*cmd_quotes(t_parser *tokens)
{
	t_parser	*list;
	int			len;

	list = tokens;
	while (list)
	{
		if (list->data->cmd)
		{
			if (check_quotes(list->data->cmd))
			{
				if (check_space(list->data->cmd))
				{
					len = len_wo_quotes(list->data->cmd);
					list->data->cmd = remove_quotes(list->data->cmd, len);	
				}
			}
		}
		list = list->next;
	}
	return (tokens);
}
