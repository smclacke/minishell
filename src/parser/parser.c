/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/10 22:11:31 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/12 17:04:06 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// i need a kind of split for the processes.........
// token_count = arr of ONE prcoess

// static void	sort_tokens(char **tokens)
// {
// 		sort through the tokens, break up into subarrs
		// organise order of subarrrs

// 	// sort order of each subarr (use old parser for this as much as possible) (in tokens struct)
// 	// add each process arr as node in parser struct
// }


// static char	*separate_tokens(char **tokens)
// {
// 	char	*one_process;
// 	int		n_tokens;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (tokens[i])
// 	{
// 		if (is_pipe(tokens[i]))
// 		{
// 			j = i;
// 			one_process = (char *)malloc(sizeof(char) * j);
// 			one_process = 
// 			return (one_process);
// 		}
// 		i++;
// 	}
// 	// malloc one_process and add all tokens, there is only one...
// 	return (one_process);
// }

// /**
//  * we need = split tokens up into their processes
//  * 
//  * echo something | < file | echo hi | << eof
//  * == 4 processes
//  * == process[0] = token[0] cmd: echo / token[1] str: something
//  * == process[1] = token[0] meta: < / token[1] file: file
//  * == process[2] = token[0] cmd: echo / token[1] str: hi
//  * == process[3] = token[0] meta: << / tkoen[1] str: eof
// */
// static t_tokens	*make_token_arr(char **tokens, int count)
// {
// 	int			i;
// 	char		**sub_arrs;

// 	i = 0;
// 	sub_arrs = (char **)malloc(sizeof(char *) * count);
// 	while (count >= 0)
// 	{
// 		sub_arrs[i] = separate_tokens(tokens);
// 		count--;
// 	}
	// int			token_count;
	// t_tokens	*token_list;

	// while (count >= 0) // make one list per process
	// {
	// 	token_count = count_tokens(tokens);
		
	// }
	// token_list = (t_tokens)malloc(sizeof(t_tokens) * token_count);
	// while ()
	// sort_tokens(tokens);
// }

/**
 * create parser token lists, sort the tokens into their sublists
*/
// void	parse_tokens(char **tokens)
// {
// 	int			i;
// 	int			count;
// 	// t_parser	*parser_arr;
// 	t_tokens	*token_arr;

// 	i = 0;
// 	count = count_procs(tokens);
// 	token_arr = make_token_arr(tokens, count);
// 	// parser_arr = (t_parser *)malloc(sizeof(t_parser) * count);
// 	// if (!parser_arr)
// 	// {
// 	// 	printf("malloc noped in parser\n");
// 	// 	exit(EXIT_FAILURE);
// 	// }
	
// 	// for each process, a token list is created...
// 	// need to figure out the whiles when not as tired
// 	// also need to free the used tokens...


// 	// make token arrs
// 	// theyre already part of the parser struct...
// }


/**
 * just make mini arrays for each proces..
 * 
*/
void		parse_tokens(char **tokens)
{
	int		i;
	int		start;
	
	int		arr;
	int		arr_index;

	int		proc_count;
	int		token_count;

	char	***mini_arrs;

	i = 0;
	start = 0;

	arr = 0;
	arr_index = 0;

	proc_count = count_procs(tokens);
	token_count = 0;

	mini_arrs = (char ***)malloc(sizeof(char **) * proc_count);
	if (!mini_arrs)
	{
		printf("oh no\n");
		exit(EXIT_FAILURE);
	}
	printf("proc_count = %i\n", proc_count);
	while (tokens[i] && arr < proc_count)
	{
		start = i;
		while (tokens[i] && !is_pipe(tokens[i]))
			i++;
		token_count = i - start;
		// printf("token_count = %i\n", token_count);
		mini_arrs[arr] = (char **)malloc(sizeof(char *) * token_count);
		while (tokens[start] && !is_pipe(tokens[start]))
		{
			mini_arrs[arr][arr_index] = tokens[start];
			arr_index++;
			start++;
		}
		// i++;
		arr++;
	}
	arr = 0;
	arr_index = 0;
	while (mini_arrs[arr])
	{
		while (mini_arrs[arr][arr_index])
		{
			printf("mini_arrs = %s\n", mini_arrs[arr][arr_index]);
			arr_index++;
		}
		arr++;
	}
	exit(EXIT_SUCCESS);
}
