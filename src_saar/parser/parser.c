/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 13:52:00 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/11 21:27:11 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static t_data_type	*handle_types(t_data_type *data, int flag)
{
	if (is_redirect(data->input))
		data->meta = data->input;
	else
	{	
		if (flag == 0)
			data->cmd = data->input;
		else
			data->strs = data->input;
	}
	return (data);
}

static t_data_type	*handle_next(t_data_type *data, char *type)
{
// need cmd after pipe, in and out files, delimiters are just strs
	printf("hello?\n");
	printf("data->input: %s\n", data->input);
	if (type == PIPE)
		data->cmd = data->input;
	else
		data->strs = data->input;
	return (data);
}

// trying to set vars that follow reds accordingly in my if statement
// need to make a function to put all the doubly shit into and just do that...
/**
 * @brief	Main parser function:
			Check the tokens to see which member of the parser struct they need to be sorted into
 * @param	tokens t_lexer tokens passed from the lexer to be sorted by the parser
 * @return	tokens: all the tokens given by the lexer have been sorted into the parser->data_type struct
*/
t_parser	*parser(t_parser *tokens)
{
	t_parser		*token_list;
	t_data_type		*data;
	char			*type;
	int				i = 0;

	token_list = tokens;
	while (token_list)
	{
		data = init_data();
		token_list->data_list = token_list->input;
		data->input = token_list->data_list;
		token_list->data_list = handle_types(data, i);
		type = is_redirect(token_list->input);
		if (type && token_list->next)
		{
			data = init_data();
			token_list = token_list->next;
			token_list->data_list = token_list->input;
			data->input = token_list->data_list;
			token_list->data_list = handle_next(data, type);
		}
		token_list = token_list->next;
		i++;
	}
	return (tokens);
}
