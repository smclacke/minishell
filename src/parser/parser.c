/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/13 17:14:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/*
	list of all input in parser list
	sort nodes into token lists
	need to know 
	- how many token lists - number of processes
	- how many tokens per list (per process)
	- 
*/
// static t_tokens	make_token_lists(t_parser *list)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (list)
// 	{
// 		while (list->input && !is_pipe(list->input))
// 		{
// 			list->process->str[j] = list->input;
// 			j++;
// 		}
// 		if (list->input && is_pipe(list->input))
// 		{
// 			free(list->input);
// 			list = list->next;
// 		}
// 		list = list->next;
// 	}
// 	return (list->process[i]);
// }

static t_parser	*make_parser_list(char **tokens)
{
	int			i;
	t_parser	*node;
	t_parser	*list;

	i = 0;
	list = NULL;
	if (!*tokens)
		return (NULL);
	while (tokens[i])
	{
		node = parser_listnew(tokens[i]);
		if (!node)
		{
			printf("aint no node!\n");
			free(tokens);
			exit(EXIT_FAILURE);
		}
		parser_listadd_back(&list, node);
		i++;
	}
	// free(tokens);
	return (list);
}

t_parser	*parse_tokens(char **tokens)
{
	t_parser	*list;
	int			i;
	// int			proc_count;

	i = 0;
	if (!tokens)
		return (NULL);
	// proc_count = count_procs(tokens);
	list = make_parser_list(tokens);
	if (!list)
		return (NULL);
	return (list);
	// ft_free_arr(tokens);
	// list->proc_count = proc_count;
	// printf("proc_count = %i\n", list->proc_count);
	// shelly_input_print(list);
	// while (proc_count >= 0)
	// {
	// 	list->process[i] = make_token_lists(list);
	// 	proc_count--;
	// 	i++;
	// }
}
