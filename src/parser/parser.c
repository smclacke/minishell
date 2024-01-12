/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/12 17:57:50 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static	t_tokens	**make_token_lists(char **tokens, t_tokens **procs)
{
	t_tokens	*node;
	t_tokens	*token_list;
	int			token_count;
	int			i;
	int			proc_i;

	i = 0;
	proc_i = 0;
	token_list = NULL;
	token_count = 0;
	while (tokens && tokens[i])
	{
		while (tokens[i] && !is_pipe(tokens[i]))
		{
			node = token_listnew(tokens[i]);
			token_listadd_back(&token_list, node);
			i++;
			token_count++;
		}
		procs[proc_i] = (t_tokens *)malloc(sizeof(t_tokens) * (token_count + 1));
		if (!procs[proc_i])
		{
			printf("procs [i] malloc failed\n");
			return (NULL);
		}
		procs[proc_i] = token_list;
		proc_i++;
		// free(token_list);
		// free(node); // maybe fixes leak or double free..
		token_list = NULL;
		token_count = 0;
		if (tokens[i])
			i++;
	}
	procs[proc_i] = 0;
	return (procs);
}

static	t_parser	*make_parser_list(t_tokens **procs, t_parser *proc_list, int proc_count)
{
	t_parser	*new_list;
	t_parser	*node;
	int			i;
	(void) proc_count;

	new_list = NULL;
	i = 0;
	while (procs[i])
	{
		printf("hoeveel?\n");
		node = parser_listnew(procs[i]);
		parser_listadd_back(&new_list, node);
		i++;
	}
	shelly_parser_print(new_list);
	proc_list = new_list;
	// free(new_list);
	// new_list = NULL;
	// free, nullify new_list
	// proc_list->next = NULL;
	return (proc_list);
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
	int			i;

	if (!tokens)
		return (NULL);
	proc_list = NULL;
	proc_count = count_procs(tokens);
	procs = (t_tokens **)malloc(sizeof(t_tokens *) * (proc_count + 1));
	if (!procs)
	{
		printf("malloc error parser\n");
		return (NULL);
	}
	procs = make_token_lists(tokens, procs);
	i = 0;
	while (procs[i])
	{
		shelly_tokenlst_print(procs[i]);
		i++;
	}
	// short contents of proc lists per var

	
	proc_list = (t_parser *)malloc(sizeof(t_parser) * (proc_count + 1));
	if (!proc_list)
	{
		printf("malloc error parser\n");
		return (NULL);
	}
	proc_list = make_parser_list(procs, proc_list, proc_count);
	i = 0;
	while (proc_list)
	{
		// proc_list->process = procs[i];
		// printf("proc_list = %s\n", (char *)proc_list->process);

		proc_list->process = proc_list->input;
		printf("proc_list = %p\n", proc_list->process);
		proc_list = proc_list->next;
	}
	return (proc_list);
}
