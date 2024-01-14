/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/14 20:02:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// static	t_parser	*make_parser_list(char ***procs, t_parser *proc_list, int proc_count)
// {
// 	t_parser	*new_list;
// 	t_parser	*node;
// 	int			i;
// 	(void) proc_count;

// 	new_list = NULL;
// 	i = 0;
// 	while (procs[i])
// 	{
// 		node = parser_listnew(procs[i]);
// 		parser_listadd_back(&new_list, node);
// 		i++;
// 	}
// 	proc_list = new_list;
// 	return (proc_list);
// }

t_parser	*parse_tokens(char **tokens)
{
	t_procs		*proc;
	t_parser	*proc_list;

	proc = (t_procs *)malloc(sizeof(t_procs));
	proc->tokens = tokens;
	proc->proc_count = count_procs(tokens);
	proc_list = NULL;
	if (proc->proc_count > 1)
	{
		proc->multi_proc = true;
		get_procs(proc);
	}
	sort_each_proc(proc, proc->multi_proc);
	proc_list = (t_parser *)malloc(sizeof(t_parser) * (proc->proc_count + 1));
	if (!proc_list)
	{
		printf("malloc error parser\n");
		return (NULL);
	}
	// proc_list = make_parser_list(proc->proc_arrs, proc_list, proc->proc_count);
	// // printing
	// shelly_parser_print(proc_list);
	// // printing

	if (proc)
		free(proc);
	return (proc_list);
}

	












	// int			proc_i;
	// int			proc_count;
	// int			i;

	// if (!tokens)
	// 	return (NULL);
	// proc_count = count_procs(tokens);
	// procs = (t_tokens **)malloc(sizeof(t_tokens *) * (proc_count + 1));
	// if (!procs)
	// {
	// 	printf("malloc error parser\n");
	// 	return (NULL);
	// }

	// proc_i = 0;
	// // make mini proc arrays, then sort per var, then add into token list (one proc)
	// // which will become node in parser list.. 
	// while (proc_i <= proc_count)
	// {
	// 	proc_arr[proc_i] = get_procs(tokens);
	// 	proc_i++;
	// }
	// i = 0;
	// while (tokens[i])
	// {
	// 	procs = make_token_lists(tokens[i], procs);
	// 	i++;
	// }
	// // procs = make_token_lists(tokens, procs);

	// // printing
	// i = 0;
	// while (procs[i])
	// {
	// 	shelly_tokenlst_print(procs[i]);
	// 	i++;
	// }
	// // printing

	// // short contents of proc lists per var
	


	// i = 0;
	// while (procs[i])
	// {
	// 	free_tokens(procs[i]);
	// 	i++;
	// }

		// sort contents, make 2d array, then add things to nodes,
			// straight away put into var nodes, skip input

/**
 * 		**strs - 2d array is one node in list, so as I make the list, check the content
 * 
 * 
 * 		process list = cmd **strs redir file
 * 
 * 
 * 		redir meta - just give as enum, then file, keep in order
 * 			
 * 
 * 			redir = enum	file  | 	redir = enum	file
 * 
 * 
*/
// static	t_tokens	**make_token_lists(char **tokens, t_tokens **procs)
// {
// 	t_tokens	*node;
// 	t_tokens	*token_list;
// 	int			token_count;
// 	int			i;
// 	int			proc_i;

// 	i = 0;
// 	proc_i = 0;
// 	token_list = NULL;
// 	token_count = 0;  

// 	// only one part of array being sent here, which is one process
// 	// find cmd, **str, redirs, and files, then add to list and send list back
// 	while (tokens && tokens[i])
// 	{
// 		while (tokens[i] && !is_pipe(tokens[i]))
// 		{
// 			node = token_listnew(tokens[i]);
// 			token_listadd_back(&token_list, node);
// 			i++;
// 			token_count++;
// 		}
// 		procs[proc_i] = (t_tokens *)malloc(sizeof(t_tokens) * (token_count + 1));
// 		if (!procs[proc_i])
// 		{
// 			printf("procs [i] malloc failed\n");
// 			return (NULL);
// 		}
// 		procs[proc_i] = token_list;
// 		proc_i++;
// 		token_list = NULL;
// 		token_count = 0;
// 		if (tokens[i])
// 			i++;
// 	}
// 	procs[proc_i] = 0;
// 	return (procs);
// }
