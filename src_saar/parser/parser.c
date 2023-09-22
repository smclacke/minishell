/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 15:06:00 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/22 14:10:41 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * while tokens and not pipe
 * sort data
 * if pipe
 * pipe -> meta
 * while tokens and not pipe
 * sort data
 * 
 * 
 * sort data = cmd flag (first one to appear is the cmd)
 * 	
*/

static t_data_type		*set_data_struct(t_parser *tokens)
{
	t_data_type	*data;

	data = init_data();
	tokens->data_type = tokens->input;
	data->input = tokens->data_type;
	return (data);
}

static int	is_pipe(void *input)
{
	if (ft_strcmp(input, PIPE) == 0)
		return (1);
	return (0);
}

t_parser	*parser(t_parser *tokens)
{
	t_parser	*token_list;
	t_data_type	*data;

	// in while for each node
	// put all token_list->input into data_type struct
	// then sort the vars in the data_type
	// give the sorted data_type struct back to token_list->data_type

	token_list = tokens;
	while (token_list)
	{
		data = init_data();
		data->input = give_data(token_list);
		while (data && !is_pipe(data->input))
		{
			// token_list->data_type = handle_vars(data);
			// find cmd, first thing that's not a redirect
			// find any reds
			// all else is strs
			data->strs = data->input;
			token_list->data_type = data;
		}
		if (is_pipe(data->input))
		{
			// token_list->data_type = handle_pipe(data);
			// below code but in func
			data->meta = data->input;
			token_list->data_type = data;
		}
		token_list = token_list->next;
	}
	return (tokens);
}

// if < or >, next is in or out, nothing else matters
// if str after < or >, in and out files (with nothing attatched to meta)
// if << here_doc 
// if >> concat out, if str after >>, out file
// if first encountered cmd, cmd
// everything else is str

