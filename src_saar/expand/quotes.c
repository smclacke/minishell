/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:55:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/02 21:54:45 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// i need a function that checks what the first quote type is, then removes
// all of those quotes but leaves any quote that is not that type
// e'c""h'o something
// ec""ho: command not found
// e'c''h'o something
// something

// strings and cmds!!


// string quotation bulllll
t_parser	*str_quotes(t_parser *tokens)
{
	t_parser	*list;
	// int			len;
	
	list = tokens;
	while (list)
	{
		if (list->str)
		{
			if (check_quotes(list->str))
			{
				printf("pseudo code\n");
				// check which is the first type of quote, remove
				// it and all of the same
				// if other quotes, keep
				// which_quotes
				// remove that specific quote (from all str)
				// keep the other type of quote
			}
		}
		list = list->next;
	}
	return (tokens);
}

/**
 * @brief	removes first encountered set of quotes and all of the same type
 * 			leaves inside quotes of a different type
 * 			e.g. "ec''ho" = ec''ho | "ec""ho" = echo
 * 			(i.e. cmd + str/flag), if so, leaves the quotes since the
 * 			cmd is invalid
 * @param	tokens from parser
 * @return	expanded tokens
*/
t_parser	*cmd_quotes(t_parser *tokens)
{
	t_parser	*list;
	int			len;
	// char		*quote_type;
	char		*cmd;

	list = tokens;
	while (list)
	{
		if (list->cmd)
		{
			cmd = list->cmd;
			if (check_quotes(cmd))
			{
				if (!check_space(cmd))
				{
					// check which is the first quote, rmove only that sort
					// quote_type = which_quote(&cmd);
					// printf("quote_type = %s\n", quote_type);
					len = len_wo_quotes(cmd);
					list->cmd = remove_quotes(cmd, len);	
				}
			}
		}
		list = list->next;
	}
	return (tokens);
}
