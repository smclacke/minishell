/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/10 22:11:31 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/11 20:44:50 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * organise in mini sub arrs, and add to token struct vars  AS LIST
 * then processes lists can be accessed by parser struct = list of processes
*/
static void	sort_tokens(char **tokens)
{
	t_tokens	input;
	char		**sub_arrs;

	input.proc_count = count_procs(tokens);
	printf("proc count = %i\n", input.proc_count);
	// subarr processes...
	// sort order of each subarr (use old parser for this as much as possible) (in tokens struct)
	// add each process arr as node in parser struct
}

void	parse_tokens(char **tokens)
{
	int			i;

	i = 0;
	while (tokens[i])
	{
		sort_tokens(tokens);
		i++;
	}
}
