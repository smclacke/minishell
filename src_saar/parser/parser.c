/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 15:06:00 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/25 20:44:23 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @brief	sorting all tokens from one process together
 * 			if no cmd has been found, the first string not
 * 			assocciated with a redrect is assigned data->cmd
 * 			is meta char? data->meta
 * 			all other input is str, token after redirect is
 * 			handled in handle_next(), (e.g. in/out files)
 * @param	data struct holding the varibale types of the lexer tokens
 * @param	flag int to check whether the cmd of the process has been found
 * @return	tokens->data passed from the data struct into the parser struct
 * 			after varibales have been assigned correctly
 * @return	tokens passed from the data struct into the parser struct
 * 			tokens with correctly assigned varibales
*/
static t_parser	*handle_vars(t_parser *data, int *flag)
{
	if (!*flag)
	{
		if (is_redirect(data->input))
			data->meta = data->input;
		else
		{
			data->cmd = data->input;
			*flag = 1;
		}
	}
	else if (*flag)
	{
		if (is_redirect(data->input))
			data->meta = data->input;
		else
			data->str = data->input;
	}
	return (data);
}

/**
 * @brief	if previous token was a meta char, the next is 
 * 			either an in or out file, or the here_doc limiter
 * 			- if < or >, next is in or out file
 *			- if << here_doc, next is limiter string
 *			- if >> concat, so outfile follows
			- don't need to handle pipes here
 * @param	data tokens
 * @param	type the previous tokens type of meta character
 * @return	tokens->data passed from the data struct into the parser struct
 * 			tokens with correctly assigned varibales
*/
static t_parser	*handle_next(t_parser *data, char *type)
{
	if (is_meta(data->input))
		data->meta = data->input;
	else if (ft_strcmp(type, LESSLESS) == 0)
		data->str = data->input;
	else
		data->file = data->input;
	return (data);
}

/**
 * @brief	if no pipe meta is encountered, handle_vars()
 * 			everything possible within one process (i.e. one cmd)
 * 			if pipe meta is found, this is added to variable struct
 * 			and the process starts from the beginning finding the 
 * 			new cmd string etc.
 * @param	data tokens
 * @param	flag int to check whether the cmd of the process has been found
 * @return	tokens with correctly assigned varibales
*/
static t_parser	*handle_all(t_parser *data, int *flag)
{
	if (data && !is_pipe(data->input))
		data = handle_vars(data, flag);
	else if (data && is_pipe(data->input))
		data = handle_pipe(data, flag);
	return (data);
}

/**
 * @brief	main parser func:
 * 			If there's a redirect, the type is saved
 * 			in type var and the next token is handled depending on
 * 			the type of redirect before it. 
 * 			handle_all() checks whether a pipe had been encountered 
 * 			or not so that the cmd can be found.
 * 			i.e. cmd str | < file CMD str str...
 * 			Flag is used to find the cmd from the strs, first str without
 * 			redirect is cmd, if pipe, this is reset.
 *  		- if < or >, next is in or out file
 *			- if << here_doc, next is limiter string
 *			- if >> concat, so outfile follows
 *			- if first encountered str, then = cmd, all others strs
 *			- if pipe, flag is reset to find the new cmd, rest works the same
 * @param	tokens t_tokens passed from the lexer to be sorted by the parser()
 * @return	tokens: all the tokens given by the lexer have been
 * 			sorted into the parser struct variables making
 * 			them more managable for the executor
*/
t_parser	*parser(t_parser *tokens)
{
	t_parser	*token_list;
	char		*type;
	int			flag;

	type = NULL;
	token_list = tokens;
	flag = 0;
	while (token_list)
	{
		type = is_redirect(token_list->input);
		token_list = handle_all(token_list, &flag);
		if (type && token_list->next)
		{
			token_list = token_list->next;
			token_list = handle_next(token_list, type);
		}
		token_list = token_list->next;
	}
	tokens = sort_list(tokens);
	tokens->n_cmd = get_no_cmds(tokens);
	return (tokens);
}
