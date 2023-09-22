/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 15:06:00 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/22 17:41:48 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static t_data_type		*handle_vars(t_data_type *data, int *flag_cmd)
{
	if (*flag_cmd == 0)
	{
		if (is_redirect(data->input))
			data->meta = data->input;
		else
		{
			data->cmd = data->input;
			*flag_cmd = 1;
		}
	}
	else if (*flag_cmd != 0)
	{	
		if (is_redirect(data->input))
			data->meta = data->input;
		else
			data->strs = data->input;
	}
	return (data);
}

static t_data_type		*handle_next(t_data_type *data, char *type)
{
	if (is_meta(data->input))
		data->meta = data->input;
	else if (ft_strcmp(type, LESSLESS) == 0) //here_doc
		data->strs = data->input;
	else
		data->file = data->input;
	return (data);
}

t_parser	*parser(t_parser *tokens)
{
	t_parser	*token_list;
	t_data_type	*data;
	int			flag_cmd = 0;
	char		*type = NULL;

	token_list = tokens;
	while (token_list)
	{
		data = init_data(token_list);
		type = is_redirect(token_list->input);
		if (data && !is_pipe(data->input))
		{
			token_list->data_type = handle_vars(data, &flag_cmd);
			if (type && token_list->next)
			{
				token_list = token_list->next;
				data = init_data(token_list);
				token_list->data_type = handle_next(data, type);
			}
		}
		if (data && is_pipe(data->input))
			token_list->data_type = handle_pipe(data, &flag_cmd);
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

