/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/10 20:06:13 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static	t_tokens	*make_token_lists(char **tokens)
{
	t_tokens	*single_proc_list;
	t_tokens	*node;
	
	single_proc_list = NULL;
	print_token_arr(tokens);
	while ()

	return (single_proc_list);
}

/**
 * - number of tokens per process
 * - number of processes
 * 
 * - split token array into separate process lists
 * - add these lists as process nodes for parser struct
 * 
 * **proc_list = {proc 1, proc 2}
 * 
 * // procs = 
 * *proc 1 = {echo, hehe} // | //
 * *proc 2 = {cd, ..}
*/
t_parser	*parse_tokens(char **tokens)
{
	t_tokens	**procs;
	t_parser	*proc_list;
	int			proc_count;
	int			token_count;
	
	if (!tokens)
		return (NULL);
	proc_list = NULL;
	proc_count = count_procs(tokens);
	printf("proc_count = %i\n", proc_count);
	
	// need this?
	// token_count = count_tokens(tokens);
	// printf("token_count = %i\n", token_count);

	procs = (t_tokens **)malloc(sizeof(t_tokens *) * proc_count);
	if (!procs)
	{
		printf("malloc error parser\n");
		return (NULL);
	}
	// this wont work, if token_count = 5, will go through 5 times, need to make list
	// based on process count...
	while (tokens)
	{
		while (proc_count >= 0)
		{
			procs[proc_count] = make_token_lists(tokens);
			proc_count--;

			// move position in token array to get next process...
		}
		// move through token list...
	}
	// proc_list ... 
	return (proc_list);
	
}

/**
 * 
 * remember = need TWO LISTS, one is a list of lists, the other is the list of tokens
 * belonging to one process
*/
/**
 * while proc_count > 0
 * 
 * add token lists as new nodes to proc_list array
 * 
 * proc_list = list_new(procs[i])
 * list add back (&proc_list, procs[i])
 * 
 * proc_count--; 
*/
