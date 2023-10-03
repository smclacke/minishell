/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:55:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/03 17:07:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @brief	removes first encountered set of quotes and all of the same type
 * 			leaves inside quotes of a different type
 * 			e.g. echo "some''thing "hi"" -> some''thing hi
 * @param	tokens from parser
 * @return	expanded tokens
*/
static t_parser	*str_quotes(t_parser *tokens)
{
	t_parser	*list;
	char		*quote_type;
	int			len;
	
	list = tokens;
	while (list)
	{
		if (list->str)
		{
			if (check_quotes(list->str))
			{
				quote_type = which_quote(list->str);
				len = len_wo_quotes(list->str, quote_type);
				list->str = remove_quotes(list->str, len, quote_type);
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
 * 			checks if there are spaces (i.e. cmd + str/flag)
 * 			if so, leaves the quotes since the cmd is invalid anyway
 * @param	tokens from parser
 * @return	expanded tokens
*/
static t_parser	*cmd_quotes(t_parser *tokens)
{
	t_parser	*list;
	char		*quote_type;
	int			len;

	list = tokens;
	while (list)
	{
		if (list->cmd)
		{
			if (check_quotes(list->cmd))
			{
				if (!check_space(list->cmd))
					list->cmd = remove_quotes(list->cmd, len, quote_type);	
			}
		}
		list = list->next;
	}
	return (tokens);
}

void	expand_quotes(t_parser *tokens)
{
	cmd_quotes(tokens);
	str_quotes(tokens);
}
