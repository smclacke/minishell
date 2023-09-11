/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 13:52:00 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/11 19:51:30 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static t_data_type	*handle_types(t_parser *tokens, int flag)
{
	t_data_type	*data;

	data = (t_data_type *)malloc(sizeof(t_data_type));
	if (!data)
		exit((EXIT_FAILURE));
	init_type_struct(data);
	tokens->data_list = tokens->input;
	data->input = tokens->data_list;
	if (is_redirect(data->input))
	{
		data->meta = data->input;
		printf("data->meta: [%s]\n", data->meta);
		if (ft_strcmp(data->input, "|") == 0)
			flag = 1;
	}
	else
	{	
		if (flag == 0 || flag == 1)
		{
			data->cmd = data->input;
			printf("data->cmd (AFTER PIPE): [%s]\n", data->cmd);
		}
		else
		{	
			data->strs = data->input;
			printf("data->strs: [%s]\n", data->strs);
		}
	}
	printf("flag = : %i\n", flag);
	return (data);
}

/**
 * @brief	Main parser function:
			Check the tokens to see which member of the parser struct they need to be sorted into
 * @param	tokens t_lexer tokens passed from the lexer to be sorted by the parser
 * @return	parser_struct: all the tokens given by the lexer have been sorted into the parser struct
*/
t_parser	*parser(t_parser *tokens)
{
	t_parser		*token_list;
	t_data_type		*type = NULL;
	int				i = 0;

	token_list = tokens;
	while (token_list)
	{
		type = handle_types(token_list, i);
		token_list->data_list = type;
		token_list = token_list->next;
		i++;
	}
	return (tokens);
}
