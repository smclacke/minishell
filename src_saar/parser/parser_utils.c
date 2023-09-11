/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:18:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/11 17:59:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	init_type_struct(t_data_type *type)
{
	type->input = NULL;
	type->strs = NULL;
	type->cmd = NULL;
	type->meta = NULL;
	type->next = NULL;
}

// bool	is_red_with_sass(t_parser *tokens)
// {
// 	if (!tokens)
// 		return (false);
// 	if (ft_strcmp(tokens->input, "|") == 0)
// 		return (true);
// 	else if (ft_strcmp(tokens->input, "<<"))
// 	return (false);
// }

/**
 * is redirect in any of the node?
*/
bool	is_redirect(t_parser *tokens)
{
	if (!tokens)
		return (false);
	if (ft_strcmp(tokens->input, ">>") == 0)
		return (true);
	else if (ft_strcmp(tokens->input, "<<") == 0)
		return (true);
	else if (ft_strcmp(tokens->input, ">") == 0)
		return (true);
	else if (ft_strcmp(tokens->input, "<") == 0)
		return (true);
	else if (ft_strcmp(tokens->input, "|") == 0)
		return (true);
	return (false);
}

t_parser	*shelly_parser_print(t_parser *tokens)
{
	t_parser	*list;
	int			i = 0;

	list = tokens;
	while (list)
	{
		printf("parser list: index [%i] | node [%s]\n", i, list->input);
		i++;
		list = list->next;
	}
	return (tokens);
}
