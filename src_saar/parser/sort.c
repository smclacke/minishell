/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 20:02:42 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/25 14:59:11 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// split this up a tiny bit....
/**
 * after finding the cmd per process, set it as the first node in list
 * at start and after each pipe to make it easier for execution
*/
t_parser	*sort_list(t_parser *tokens)
{
	t_parser	*head;
	t_parser	*tmp;
	t_parser	*new;
	t_parser	*new_node;
	t_parser	*tmp2;
	int			sign = 0;

	head = tokens;
	tmp = tokens;
	new = NULL;
	while (tmp && !sign)
	{
		if (tmp->cmd)
		{
			new_node = lexer_listnew(tmp->cmd);
			new_node->cmd = tmp->cmd;
			lexer_listadd_back(&new, new_node);
			tmp->flag = 1;
			sign = 42;
		}
		tmp = tmp->next;
	}
	tmp = tokens;
	sign = 0;
	while (tmp)
	{
		if (!tmp->flag && shelly_strcmp(tmp->meta, "|") == 0)
		{
			new_node = lexer_listnew(tmp->meta);
			new_node->meta = tmp->meta;
			lexer_listadd_back(&new, new_node);
			tmp->flag = 1;
			tmp2 = tmp;
			tmp2 = tmp2->next;
			while (tmp2 && !tmp2->flag)
			{
				if (tmp2->cmd)
				{
					new_node = lexer_listnew(tmp2->cmd);
					new_node->cmd = tmp2->cmd;
					lexer_listadd_back(&new, new_node);
					tmp2->flag = 1;
				}
				tmp2 = tmp2->next;
			}
		}
		if (!tmp->flag && tmp->file)
		{
			new_node = lexer_listnew(tmp->file);
			new_node->file = tmp->file;
			lexer_listadd_back(&new, new_node);
			tmp->flag = 1;
		}
		if (!tmp->flag && tmp->str)
		{
			new_node = lexer_listnew(tmp->str);
			new_node->str = tmp->str;
			lexer_listadd_back(&new, new_node);
			tmp->flag = 1;
		}
		if (!tmp->flag && tmp->meta)
		{
			new_node = lexer_listnew(tmp->meta);
			new_node->meta = tmp->meta;
			lexer_listadd_back(&new, new_node);
			tmp->flag = 1;
		}
		tmp = tmp->next;
		sign++;
	}
	shelly_print_list(new);
	return (new);
}
