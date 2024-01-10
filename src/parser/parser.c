/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/10 19:58:38 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static	t_tokens	*make_token_lists(char **tokens)
{
	t_tokens	*node;

	while ()
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
	
	token_count = count_tokens(tokens);
	printf("token_count = %i\n", token_count);

	procs = (t_tokens **)malloc(sizeof(t_tokens *) * proc_count);
	if (!procs)
	{
		printf("malloc error parser\n");
		return (NULL);
	}

	while (token_count > 0)
	{
		*procs = make_token_lists(tokens);
		token_count--;
	}
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
