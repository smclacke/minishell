/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   more_sort.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/10 21:37:34 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/10 22:04:40 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// ORRR, after sorting everything into different kinds of vars
// figure what is what...

// take from each process, all the args to a cmd, put them after cmd
// then add any metas/files to the end...
// basically sort 2.0 
// fuck yeah

/**
 * if there is a cmd, then it's going to be at the start..
 * then, while no pipe, if str, add to front of cmd (push swap tokens)
 * 
 * 
 * 
 * NO DIFFERENT
 * 
 * while list and no pipe, if meta or file, move to end (BEFORE PIPE), run through
 * list keeping these in order
*/

// t_process	*sort_processes(t_parser *tokens)
// {
// 	t_parser	*tmp;
// 	t_process	*new_list;

// 	if (!tokens)
// 		return (NULL);
// 	tmp = tokens;
// 	new_list = NULL;
// 	while (tmp)
// 	{
// 		while (tmp && shelly_strcmp(tmp->meta, "|") != 0)
// 		{
// 		}

// 		tmp = tmp->next;
// 	}
// }

// static int	count_tokens(t_parser *tokens)
// {
// 	t_parser	*tmp;

// 	while 
// }

// int	create_process_struct(t_parser *tokens)
// {
// 	t_process	*processes;
// 	int			token_count;

// 	token_count = count_tokens(tokens);
	
// 	processes = malloc(sizeof(t_process) * token_count);
// }

// int	sort_shit_out(t_parser *tokens)
// {
// 	t_parser	*tmp;
// 	t_parser	*tmp_list;

// 	tmp = tokens;
// 	tmp_list = NULL;
// 	while (tmp)
// 	{
// 		while (shelly_strcmp(tmp->meta, "|") == 0)
// 		{
// 			tmp_list = add_to_tmp(tmp, tmp_list)
// 		}
// 		if (shelly_strcmp(tmp->meta, "|") == 0)
// 		{
// 			create_process_struct(tmp)
// 		}
// 		tmp = tmp->next;
// 	}
// }
