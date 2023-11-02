/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 16:12:50 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/02 18:19:19 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo errors
*/

t_parser	*add_new_str(t_parser *tmp, t_parser *new_list, char *str)
{
	t_parser	*new_node;

	new_node = lexer_listnew(str);
	if (!new_node)
		mini_error("add_str fucked", errno);
	lexer_listadd_back(&new_list, new_node);
	new_node->str = str;
	tmp->flag = 1;
	if (!new_list)
		mini_error("bad 0", errno);
	return (new_list);
}

t_parser	*add_new_file(t_parser *tmp, t_parser *new_list, char *file)
{
	t_parser	*new_node;

	new_node = lexer_listnew(file);
	if (!new_node)
		mini_error("add_file fucked", errno);
	lexer_listadd_back(&new_list, new_node);
	new_node->file = file;
	tmp->flag = 1;
	if (!new_list)
		mini_error("bad 1", errno);
	return (new_list);
}

t_parser	*add_new_meta(t_parser *tmp, t_parser *new_list, char *meta)
{
	t_parser	*new_node;

	new_node = lexer_listnew(meta);
	if (!new_node)
		mini_error("add_meta fucked", errno);
	lexer_listadd_back(&new_list, new_node);
	new_node->meta = meta;
	tmp->flag = 1;
	if (!new_list)
		mini_error("bad 2", errno);
	return (new_list);
}

t_parser	*add_new_cmd(t_parser *tmp, t_parser *new_list, char *cmd)
{
	t_parser	*new_node;

	new_node = lexer_listnew(cmd);
	if (!new_node)
		mini_error("add_cmd fucked", errno);
	lexer_listadd_back(&new_list, new_node);
	new_node->cmd = cmd;
	tmp->flag = 1;
	if (!new_list)
		mini_error("bad 3", errno);
	return (new_list);
}
