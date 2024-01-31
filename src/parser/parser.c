/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/30 12:53:56 by eugene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo	maybe norm?
 * @todo	error handling
 * @todo	memory handling, malloc protection
 * @todo	remove print statements when everything works
 * @todo 	do I need alllll of these vars??
*/
t_parser	*parse_tokens(char **tokens)
{
	t_parser	*proc;
	t_parser	*parser_list;
	t_parser	*new_node;
	int			i;

	i = 0;
	proc = (t_parser *)malloc(sizeof(t_parser));
	// wrap it up
	ft_bzero(proc, sizeof(t_parser));

	proc->tokens = tokens;
	proc->proc_count = count_procs(tokens);

	parser_list = NULL;
	new_node = NULL;

	if (proc->proc_count > 0)
	{
		proc->multi_proc_b = TRUE;
		get_procs(proc);
		while (i < proc->proc_count)
		{
			sort_each_proc(proc, proc->proc_arrs[i], i);
			new_node = parser_listnew(proc->process[i]);
			parser_listadd_back(&parser_list, new_node);
			i++;
		}
	}	
	else if (proc->proc_count == 0)
	{
		proc->multi_proc_b = FALSE;
		sort_each_proc(proc, proc->tokens, i);
		new_node = parser_listnew(proc->process[i]);
		parser_listadd_back(&parser_list, new_node);
	}
	print_parser(parser_list);
	return (parser_list);
}
