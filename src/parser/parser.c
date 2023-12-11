/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/10 22:11:31 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/11 18:31:50 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static t_parser	sort_data(t_parser *tokens)
{
	t_parser		*tmp;
	t_parser		single_process;
	char			*type;
	int				flag;

	tmp = tokens;
	while (tmp)
	{
		type = is_redirect(tmp->input);
		single_process = *handle_input(tmp, &flag);
		if (type && tmp->next)
		{
			tmp = tmp->next;
			single_process = *handle_next(tmp, type);
		}
		else if (type && !tmp->next)
			exit(EXIT_FAILURE); //error
		tmp = tmp->next;
	}
	return (single_process);
}

static t_parser *init_parser_structs(t_process *data, t_parser *parser_array)
{
	int				i;
	int				count;
	t_parser		*tmp;
	t_parser		single_process;

	i = 0;
	count = data->proc_count;
	tmp = data->parser;
	while (tmp)
	{
		while (i < count)
		{
			single_process.proc_id = i;
			while (tmp && !is_pipe(tmp->input))
			{
				single_process = sort_data(tmp);
				tmp = tmp->next;
				parser_array[i] = single_process;
			}
			if (tmp && is_pipe(tmp->input))
				tmp = tmp->next;
			i++;
		}
	}
	free(tmp);
	// free input somewhere
	return (parser_array);
}	

static void	get_proc_count(t_process *data)
{
	t_parser		*tmp;
	int				proc_count;

	tmp = data->parser;
	proc_count = 1;
	while (tmp)
	{
		if (shelly_strcmp(tmp->input, "|") == 0)
		{
			tmp = tmp->next;
			proc_count++;
		}
		tmp = tmp->next;
	}
	data->proc_count = proc_count;
	printf("proc_count = %i\n", data->proc_count);
}

/**
 * takes process struct, uses tokens from lexer in init func
*/
void	parser(t_process *data)
{
	t_parser	*parser_array;

	get_proc_count(data);
	parser_array = malloc(sizeof(t_parser) * data->proc_count); // protect
	parser_array = init_parser_structs(data, parser_array); // protect
	free_input(data);
	// freeeeeee lexer token list, here or main??
	data->parser = parser_array;
}


