/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 20:02:42 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/25 17:17:04 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static t_parser	*find_first_cmd(t_parser *tmp, t_parser *new_list)
{
	t_parser	*lst;
	int			sign;

	lst = tmp;
	sign = 0;
	while (lst && !sign)
	{
		if (lst->cmd)
		{
			new_list = add_new_cmd(lst, new_list, lst->cmd);
			sign = 42;
		}
		lst = lst->next;
	}
	return (new_list);
}

static t_parser	*cmd_after_pipe(t_parser *tmp, t_parser *new_list)
{
	t_parser	*tmp2;

	tmp2 = tmp;
	tmp2 = tmp2->next;
	while (tmp2 && !tmp2->flag && shelly_strcmp(tmp2->meta, "|") != 0)
	{
		if (tmp2->cmd)
			new_list = add_new_cmd(tmp2, new_list, tmp2->cmd);
		tmp2 = tmp2->next;
	}
	return (new_list);
}

/**
 * after finding the cmd per process, set it as the first node in list
 * at start and after each pipe to make it easier for the executor
*/
t_parser	*sort_list(t_parser *tokens)
{
	t_parser	*tmp;
	t_parser	*new_list;
	int			sign;

	sign = 0;
	tmp = tokens;
	new_list = NULL;
	new_list = find_first_cmd(tmp, new_list);
	while (tmp)
	{
		if (!tmp->flag && shelly_strcmp(tmp->meta, "|") == 0)
		{
			new_list = add_new_meta(tmp, new_list, tmp->meta);
			new_list = cmd_after_pipe(tmp, new_list);
		}
		if (!tmp->flag && tmp->file)
			new_list = add_new_file(tmp, new_list, tmp->file);
		if (!tmp->flag && tmp->str)
			new_list = add_new_str(tmp, new_list, tmp->str);
		if (!tmp->flag && tmp->meta)
			new_list = add_new_meta(tmp, new_list, tmp->meta);
		tmp = tmp->next;
	}
	return (new_list);
}
