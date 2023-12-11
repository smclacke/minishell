/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/10 22:11:31 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/11 17:58:06 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * VERY FUCKING SIMPLE
 * 
 * i have tokens.... yay
 * find pipe 
 * take everything up to pipe
 * put in mini linked list
 * make array of mini linked lists
 * 
 * die in the hell that is mini
 * bye
*/

static t_parser	sort_data(t_lexer *tokens)
{
	t_lexer		*tmp;
	char		*type;
	int			flag;

	tmp = tokens;
	while (tmp)
	{
		type = is_redirect(tmp->input);
		
	}
}

static t_parser *init_parser_structs(t_process *data, t_parser *parser_array)
{
	int			i;
	t_lexer		*tmp;
	t_parser	single_process;
	int			count;

	i = 0;
	tmp = data->tokens;
	count = data->proc_count;
	while (tmp)
	{
		while (i < count)
		{
			if (shello_strcmp(tmp->input, "|") == 0)
			{
				tmp = tmp->next;
				free(tmp);
			}
			while (shelly_strcmp(tmp->input, "|") != 0)
			{
				single_process.proc_id = i;
				single_process = sort_data(tmp);
				tmp = tmp->next;
				free(tmp);
				parser_array[i] = single_process;
			}
			i++;
		}
	}
	return (parser_array);
}	

static void	get_proc_count(t_process *data)
{
	t_lexer		*tmp;
	int			proc_count;

	tmp = data->tokens;
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
	data->proc = parser_array;
}


