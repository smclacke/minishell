/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/17 19:08:44 by SarahLouise   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

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

static int	total_token_len(char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}	

static char	**trim_tokens(char **tokens, int i)
{
	char	**trimmed;
	int		trim_i;
	int		new_len;
	int		total_len;
	int		used_len;

	trim_i = 0;
	total_len = total_token_len(tokens);
	used_len = i;
	new_len = total_len - used_len;
	trimmed = (char **)malloc(sizeof(char *) * (new_len + 1));
	while (tokens[i])
	{
		trimmed[trim_i] = tokens[i];
		i++;
		trim_i++; 
	}
	trimmed[trim_i] = 0;
	return (trimmed);
}

static t_tokens	make_token_lists(char **tokens, int proc_i)
{
	t_tokens	*token_list;
	t_tokens	*node;
	char		**tmp;
	int			token_i;

	token_i = 0;
	token_list = NULL;
	tmp = NULL;
	print_token_arr(tokens);
	while (tokens[token_i])
	{
		// print_token_arr(tokens);
		while (tokens[token_i] && !is_pipe(tokens[token_i]))
		{
			node = token_listnew(tokens[token_i]);
			token_listadd_back(&token_list, node);
			token_i++;
		}
		if (tokens[token_i] && is_pipe(tokens[token_i]))
		{
			tmp = tokens;
			if (tokens[token_i + 1])
				tokens = trim_tokens(tmp, (token_i + 1));
			// int		i = 0;
			// while (tokens[i])
			// {
			// 	printf("trimmmed = %s\n", tokens[i]);
			// 	i++;
			// }
		}
	}
	return (token_list[proc_i]);
}

// static t_parser	*other_listnew(t_tokens *input)
// {
// 	t_parser	*new;

// 	new = (t_parser *)malloc(sizeof(t_parser));
// 	if (!new || !input)
// 	{
// 		// free(input); // errrm??
// 		printf("erroroororr\n");
// 		return (0);
// 	}
// 	ft_bzero(new, sizeof(t_parser));
// 	new->process = input;
// 	new->next = NULL;
// 	return (new);
// }

// static t_parser	*make_parser_list(t_tokens *process)
// {
// 	t_parser	*list;
// 	t_parser	*node;

// 	list = NULL;
// 	while (process)
// 	{
// 		node = other_listnew(process);
// 		parser_listadd_back(&list, node);
// 		process = process->next;
// 	}
// 	return (list);
// }

t_parser	*parse_tokens(char **tokens)
{
	t_tokens	*process;
	t_parser	*list;
	int			proc_i;
	// int			nog_proc;
	int			proc_count;

	// nog_proc = 0;
	if (!tokens)
		return (NULL);
	proc_i = 0;
	list = NULL;
	proc_count = count_procs(tokens);
	process = (t_tokens *)malloc(sizeof(t_tokens) * proc_count);
	while (proc_count > 0)
	{
		*process = make_token_lists(tokens, proc_i);
		// printf("process in while = %p\n", process);
		proc_count--;
		// proc_i++;
	}
	printf("ret after while\n");
	// proc_count = count_procs(tokens);
	// proc_i = 0;
	// while (process[proc_i])
	// {
	// 	printf("process ptrs = %p\n", process[proc_i]);
	// 	proc_i++;
	// }
	shelly_tokenlst_print(process);
	// list = make_parser_list(process);
	// shelly_parser_print(list);
	return (list);
}
