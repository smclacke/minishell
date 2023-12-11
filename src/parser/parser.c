/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/10 22:11:31 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/11 21:43:07 by smclacke      ########   odam.nl         */
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

static t_tokens	*make_token_arr(char **tokens)
{
	int			token_count;
	t_tokens	*token_list;

	token_count = count_tokens(tokens);
	token_list = (t_tokens)malloc(sizeof(t_tokens) * token_count);
	// sort_tokens(tokens);
}

/**
 * create parser token lists, sort the tokens into their sublists
*/
void	parse_tokens(char **tokens)
{
	int			i;
	int			count;
	t_parser	*parser_arr;
	t_tokens	*token_arr;

	i = 0;
	count = count_procs(tokens);
	parser_arr = (t_parser *)malloc(sizeof(t_parser) * count);
	if (!parser_arr)
	{
		printf("malloc noped in parser\n");
		exit(EXIT_FAILURE);
	}
	// for each process, a token list is created...
	// need to figure out the whiles when not as tired
	// also need to free the used tokens...
	while (parser_arr)
	{
		while (tokens[i])
		{
			token_arr = make_token_arr(tokens);
			i++;
		}
		parser_arr = parser_arr->next;
			
	}
	// add token_arrs to parser_arr...
}
