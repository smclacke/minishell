/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 13:52:00 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/20 19:58:26 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @brief	checks whether the input token is a redirect
 * 			if so, token->data_type = meta
 * 			otherwise, checks whether it's the first token
 * 			if so, token->data_type = cmd
 * 			otherwise, the input is initialized as a strs
 * @param	data pasing the data var form the data_type struct 
 * 			so initialize it's input correctly into it's struct
 * @param	flag checks whether this is the first token, 
 * 			if so it is initialized as cmd
 * @return	data: parser->data_type back to the parser function to 
 * 			move on to sort the next token
*/
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

/**
 * @brief	if previous token was a redirect, 
 * 			the following one is going to be cmd, file or delimiter
 * 			same thing as handle_types but now checks 
 * 			which meta type came before
 * @param	data pasing the data var form the data_type struct 
 * 			so initialize it's input correctly into it's struct
 * @param	type type of meta from the token before this 
 * 			current one that's now being handled
 * @return	data: parser->data_type back to the parser function 
 * 			to move on to sort the next token
*/
static t_data_type	*handle_next(t_data_type *data, char *type)
{
	if (ft_strnstr(type, PIPE, 1))
	{
		if (is_meta(data->input))
			data->file = data->input;
		else
			data->cmd = data->input;
	}
	else if (ft_strcmp(type, LESSLESS) == 0)
		data->strs = data->input;
	else
		data->file = data->input;
	return (data);
}

/**
 * @brief	Takes the t_parser tokens, puts the input into 
 * 			the t_parser data_type (struct) varibale
 * 			called data and returns to main parser function 
 * 			so the input can be sorted accordingly
 * @param	tokens input from parser struct that is put into the direct struct
 * @param	data data_type struct variable to use in handle functions
 * @return	data->input: input put into the data_type struct to be 
 * 			sorted in the struct by correct var type in the handle functions
*/
static void	*give_data(t_parser *tokens, t_data_type *data)
{
	tokens->data_type = tokens->input;
	data->input = tokens->data_type;
	return (data->input);
}

/**
 * @brief	Main parser function:
 *			takes the tokens, puts them into the data_type struct 
 *			and then sorts them based on there position into the correct 
 *			data_type struct variable, returning the new sorted token 
 *			list to the executor
 * @param	tokens t_parser tokens passed from the lexer 
 * 			to be sorted by the parser()
 * @return	tokens: all the tokens given by the lexer have been 
 * 			sorted into the parser->data_type struct
 * 			making them more managable for the executor
*/
t_parser	*parser(t_parser *tokens)
{
	t_parser		*token_list;
	t_data_type		*data;
	char			*type;
	int				i;

	i = 0;
	token_list = tokens;
	while (token_list)
	{
		data = init_data();
		data->input = give_data(token_list, data);
		token_list->data_type = handle_types(data, i);
		type = is_redirect(token_list->input);
		if (type && token_list->next)
		{
			token_list = token_list->next;
			data = init_data();
			data->input = give_data(token_list, data);
			token_list->data_type = handle_next(data, type);
		}
		token_list = token_list->next;
		i++;
	}
	return (tokens);
}
