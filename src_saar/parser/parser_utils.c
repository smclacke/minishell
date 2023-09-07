/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:18:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/07 19:29:59 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	init_cmd_struct(t_command *cmds)
{
	cmds->input = NULL;
	cmds->strs = NULL;
	cmds->cmd = NULL;
	cmds->next = NULL;
}

void	init_red_struct(t_redirect *reds)
{
	reds->input = NULL;
	reds->meta = NULL;
	// reds->file = NULL;
	reds->next = NULL;
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
	else if (ft_strcmp(tokens->input, "$") == 0)
		return (true);
	else if (ft_strcmp(tokens->input, "|") == 0)
		return (true);
	return (false);
}

// SPLIT METAS IN LEXER SO THIS ISN'T NECESSARY ANYMORE
// /**
//  * is redirect the only thing in node? ( file is not attached )
// */
// bool	file_attached(t_parser *tokens)
// {
// 	if (!tokens)
// 		return (false);
// 	if (ft_strcmp(tokens->input, ">>") == 0)
// 		return (false);
// 	else if (ft_strcmp(tokens->input, "<<") == 0)
// 		return (false);
// 	else if (ft_strcmp(tokens->input, ">") == 0)
// 		return (false);
// 	else if (ft_strcmp(tokens->input, "<") == 0)
// 		return (false);
// 	else if (ft_strcmp(tokens->input, "$") == 0)
// 		return (false);
// 	return (true);
// }

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
