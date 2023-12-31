/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 15:06:00 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/10 20:22:53 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo errors
*/

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
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
static t_parser	*handle_vars(t_parser *data, int *flag)
{
	if (!*flag)
	{
		if (is_meta_no_pipe(data->input))
			data->meta = data->input;
		else
		{
			data->cmd = data->input;
			*flag = 1;
		}
	}
	else if (*flag)
	{
		if (is_meta_no_pipe(data->input))
			data->meta = data->input;
		else
			data->str = data->input;
	}
	if (!data)
		// mini_error("general: handle_vars()", E_GENERAL);
		return (0);
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
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
static t_parser	*handle_next(t_parser *data, char *type)
{
	if (is_meta(data->input))
		// mini_error("syntax error near expected token 'TOKEN'", E_SYNTAX);
		return (0);
	if (ft_strcmp(type, LESSLESS) == 0)
		data->hd_limit = data->input;
	else
		data->file = data->input;
	if (!data)
		// mini_error("general: handle_next()", E_GENERAL);
		return (0);
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
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
static t_parser	*handle_input(t_parser *data, int *flag)
{
	if (data && !is_pipe(data->input))
		data = handle_vars(data, flag);
	else if (data && is_pipe(data->input))
		data = handle_pipe(data, flag);
	if (!data)
		// mini_error("general: handle_input()", E_GENERAL);
		return (0);
	return (data);
}

static int	get_n_pipe(t_parser *tokens)
{
	t_parser	*tmp;
	int			i;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->meta && shelly_strcmp(tmp->meta, "|") == 0)
			i += 1;
		tmp = tmp->next;
	}
	return (i);
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
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
t_parser	*parser(t_parser *tokens)
{
	t_parser	*tmp;
	char		*type;
	int			flag;

	tmp = tokens;
	type = NULL;
	flag = 0;
	while (tmp)
	{
		type = is_redirect(tmp->input);
		tmp = handle_input(tmp, &flag);
		if (type && tmp->next)
		{
			tmp = tmp->next;
			tmp = handle_next(tmp, type);
		}
		else if (type && !tmp->next)
			return (0); // errror
		tmp = tmp->next;
	}
	tokens = sort_list(tokens);
	tokens->n_cmd = get_n_cmds(tokens);
	tokens->n_pipe = get_n_pipe(tokens);
	return (tokens);
}
