/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/13 18:21:22 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// static	int		tokens_per_process(list)
// {
	
// }

static char	**trim_tokens(char **tokens, int i)
{
	char	**trimmed;
	int		trim_i;

	trim_i = 0;
	while (tokens[i])
	{
		trimmed[trim_i] = tokens[i];
		i++;
		trim_i++; 
	}
	return (trimmed);
}

static t_tokens	make_token_lists(char **tokens, int proc_i)
{
	t_tokens	*token_list;
	t_tokens	*node;
	int			no_tokens;
	int			token_i;

	token_i = 0;
	// no_tokens = tokens_per_process(tokens);
	// trim the array (before / after?) or just run through it??
	while (tokens[token_i]) // up to number of tokens in this process...
	{
		while (tokens[token_i] && !is_pipe(tokens[token_i]))
		{
			node = parser_list_new(tokens[token_i]);
			parser_listadd_back(&token_list, node);
			token_i++;
		}
		if (tokens[token_i] && is_pipe(tokens[token_i]))
		{
			*tokens = trim_tokens(tokens, (token_i + 1));
			return (token_list[proc_i]);
		}
	}
	return (token_list[proc_i]);
}

/**
 * one func to split array into processes, and one func to add to
 * 	token list, these lists are passed back from here to parse_tokens()
 * 
 * HERE:
 * parser list nodes = no.processes, NULL list here, then add with token lists
 * we have the no. of process, we need to init parser list (process ... ?)
 * add the token lists to process nodes
 * 
 * 
 * MAKE MINI LISTS, ADD TO PARSER LIST...
 * how to go from mini lists to making parser list to add token lists to parser list...
 * 
 * REALLLY not sure about initing the parser struct, so coming back to it...
 * 
 * RIGHTNOW:
 * for each process (while loop) add token list from make_token_lists()
 * USING str array not a list!!
*/
t_parser	*parse_tokens(char **tokens)
{
	t_parser	*list;
	int			proc_i;
	int			proc_count;

	proc_i = 0;
	if (!tokens)
		return (NULL);
	proc_count = count_procs(tokens);
	printf("proc_count = %i\n", list->proc_count);
	shelly_input_print(list);
	while (proc_count >= 0)
	{
		// return token list each time, adding to parser list
		list->process[proc_i] = make_token_lists(tokens, proc_i);
		proc_count--;
		proc_i++;
	}
	return (list);
}
