/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/12 18:53:01 by smclacke      ########   odam.nl         */
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

static t_parser	*make_parser_list(t_parser *list, char **tokens)
{
	int			i;
	t_parser	*node;

	i = 0;
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
	return (list);
}

void	parse_tokens(char **tokens)
{
	t_parser	*list;
	int			i;
	int			proc_count;

	list = NULL;
	i = 0;
	proc_count = count_procs(tokens);
	list = make_parser_list(list, tokens);
	if (!list)
	{
		free(tokens);
		exit(EXIT_FAILURE);		
	}
	free(tokens);
	list->proc_count = proc_count;
	printf("proc_count = %i\n", list->proc_count);
	shelly_input_print(list);
	// while (proc_count >= 0)
	// {
	// 	list->process[i] = make_token_lists(list);
	// 	proc_count--;
	// 	i++;
	// }
}
