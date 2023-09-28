/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:55:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/28 16:40:33 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @brief	removes both single and double quotes from in and around cmds
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
				printf("cmd with quotes = %s\n", list->data->cmd);
				len = len_wo_quotes(list->data->cmd);
				printf("len = %i\n", len);
				list->data->cmd = remove_quotes(list->data->cmd, len);
				printf("cmd wo quotes = %s\n", list->data->cmd);
			}
		}
		list = list->next;
	}
	return (tokens);
}
