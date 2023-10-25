/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 20:02:42 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/25 15:57:21 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static t_parser	*add_new_cmd(t_parser *new_list, char *cmd)
{
	t_parser	*new_node;
	
	new_node = lexer_listnew(cmd);
	lexer_listadd_back(&new_list, new_node);
	new_node->cmd = cmd;
	return (new_list);
}

// split this up a tiny bit....
/**
 * after finding the cmd per process, set it as the first node in list
 * at start and after each pipe to make it easier for the executor
*/
t_parser	*sort_list(t_parser *tokens)
{
	t_parser	*tmp;
	t_parser	*tmp2;
	t_parser	*new_list;
	t_parser	*new_node;
	int			sign;

	sign = 0;
	tmp = tokens;
	new_list = NULL;
	new_node = NULL;
	while (tmp && !sign)
	{
		if (tmp->cmd)
		{
			new_list = add_new_cmd(new_list, tmp->cmd);
			// new_node = lexer_listnew(tmp->cmd);
			// lexer_listadd_back(&new_list, new_node);
			// new_node->cmd = tmp->cmd;
			tmp->flag = 1;
			sign = 42;
		}
		tmp = tmp->next;
	}
	tmp = tokens;
	while (tmp)
	{
		if (!tmp->flag && shelly_strcmp(tmp->meta, "|") == 0)
		{
			new_node = lexer_listnew(tmp->meta);
			lexer_listadd_back(&new_list, new_node);
			new_node->meta = tmp->meta;
			tmp->flag = 1;
			tmp2 = tmp;
			tmp2 = tmp2->next;
			while (tmp2 && !tmp2->flag && shelly_strcmp(tmp2->meta, "|") != 0)
			{
				if (tmp2->cmd)
				{
					new_node = lexer_listnew(tmp2->cmd);
					new_node->cmd = tmp2->cmd;
					lexer_listadd_back(&new_list, new_node);
					tmp->flag = 1;
					tmp2->flag = 1;
				}
				tmp2 = tmp2->next;
			}
		}
		if (!tmp->flag && tmp->file)
		{
			new_node = lexer_listnew(tmp->file);
			lexer_listadd_back(&new_list, new_node);
			new_node->file = tmp->file;
			tmp->flag = 1;
		}
		if (!tmp->flag && tmp->str)
		{
			new_node = lexer_listnew(tmp->str);
			lexer_listadd_back(&new_list, new_node);
			new_node->str = tmp->str;
			tmp->flag = 1;
		}
		if (!tmp->flag && tmp->meta)
		{
			new_node = lexer_listnew(tmp->meta);
			lexer_listadd_back(&new_list, new_node);
			new_node->meta = tmp->meta;
			tmp->flag = 1;
		}
		tmp = tmp->next;
	}
	return (new_list);
}
