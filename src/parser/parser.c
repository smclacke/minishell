/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/12 18:29:54 by smclacke      ########   odam.nl         */
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
static t_tokens	make_token_lists(t_parser *list)
{
	int		i;

	i = 0;
	while (list->input)
	{
		while (list->input && !is_pipe(list->input))
		{
			list->process->node = list->input;
		}
	}
	return (list->process[i]);
	
}

static t_parser	*make_parser_list(t_parser *list, char **tokens)
{
	int			i;
	t_parser	*node;

	i = 0;
	while (tokens[i])
	{
		node = lexer_listnew(tokens[i]);
		if (!node)
		{
			printf("aint no node!\n");
			exit(EXIT_FAILURE);
		}
		lexer_listadd_back(&list, node);
		i++;
	}
	free(tokens);
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
	list->proc_count = proc_count;
	while (proc_count >= 0)
	{
		list->process[i] = make_token_lists(list);
		proc_count--;
		i++;
	}
}
