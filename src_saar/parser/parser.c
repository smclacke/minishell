/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/03 13:39:49 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * I need a, this is a string with quotes check and then like thousands of functions to handle that
*/

/**
 * @brief	Checking whether the first arg token is valid:
 * 			$, <<. >>, <, >, or absolute path. Builtin has been checked in format_check()
 * 			~ Add check for other cmds somehow ~
 * 			The rest of the arg tokens are checked in define_token
 * @param	tokens first arg token passed from the lexer to the parser
 * @param	parser_struct  structure to assign each token to the correct member within parser struct
 * @return	bool: true/false 1/0
*/
static bool	parser_define_first_token(t_lexer *tokens, t_parser  *parser_struct)
{
	if (!tokens)
		return (false);
	if (parser_cmp_signs(tokens))
	{
		parser_struct->sign = tokens->input;
		printf("first->sign: %s\n", parser_struct->sign);
		return (true);
	}
	else if (parser_cmp_builtins(tokens))
	{	
		parser_struct->cmd = tokens->input;
		printf("first->cmd: %s\n", parser_struct->cmd);
		return (true);
	}
	else if (parser_cmp_abso(tokens))
	{
		parser_struct->abso = tokens->input; // will at some point need to validate the paths...
		printf("first->abso: %s\n", parser_struct->abso);
		return (true);	
	}
	return (false);
}

/**
 * @brief	assigns the tokens to a member in the parser struct:
 * 			sign, pipe, absolute path or str. Builtins are already checked in format_check()
 * @param	tokens passed from the lexer, first token has already been handled in parser_define_first_token()
 * @param	parser_struct  structure to assign each token to the correct member within parser struct
 * @return	assigns the token input to a member in the parser struct
*/
static void	*parser_define_tokens(t_lexer *tokens, t_parser *parser_struct)
{
	if (!tokens)
		return (false);
	if (parser_cmp_signs(tokens))
	{
		parser_struct->sign = tokens->input;
		printf("second->sign: %s\n", parser_struct->sign);
	}
	else if (parser_cmp_pipe(tokens))
	{
		parser_struct->sign = tokens->input;
		printf("second->sign: %s\n", parser_struct->sign);
	}
	else if (parser_cmp_builtins(tokens))
	{	
		parser_struct->cmd = tokens->input;
		printf("second->cmd: %s\n", parser_struct->cmd);
	}
	else if (parser_cmp_abso(tokens))
	{	
		parser_struct->abso = tokens->input;
		printf("second->abso: %s\n", parser_struct->abso);
	}
	else
	{
		parser_struct->str = tokens->input;
		printf("second->str: %s\n", parser_struct->str);
	}
	return (0);
}

/**
 * @brief	take all tokens, put input into a temp, remove the quotes and make lowercase
 * 			test if it's a buildin, if yes, return the temp as this is valid
 * 			else, return the original input to test against signs etc
 * @param	tokens passed from lexer, being sorted and put into the parser struct
 * @param	parser_struct structure to assign each token to the correct member within parser struct
 * @return	bool: true/false 1/0   
*/
static bool	parser_format_check(t_lexer *tokens, t_parser *parser_struct)
{
	char	*tmp;

	tmp = tokens->input;
	ft_lower_str(tmp);
	if (parser_check_quotes(tokens->input))
	{
		tmp = remove_quotes(tokens->input);
		if (!tmp)
			return (0);
		if (parser_cmp_char_builtins(tmp))
		{
			parser_struct->cmd = tmp;
			return (true);
		}
	}
	return (false);
}

void	init_parser(t_parser *parser_struct)
{
	parser_struct->str = NULL;
	parser_struct->cmd = NULL;
	parser_struct->sign = NULL;
	parser_struct->abso = NULL;
}

/**
 * @brief	Main parser function: check vadility of first token
			Check the rest of the tokens to see which member of the parser struct they need to be sorted into
			Return the new parser_struct to the expander
 * @param	tokens t_lexer tokens passed from the lexer to be sorted by the parser
 * @return	parser_struct: all the tokens given by the lexer have been sorted into the parser struct. The first argument is checked for its validity
*/
t_parser	*parser(t_lexer *tokens)
{
	t_parser	*parser_struct;
	t_lexer		*list;

	parser_struct = (t_parser *)malloc(sizeof(t_parser));
	if (!parser_struct)
		return (0);
	init_parser(parser_struct);
	if (!parser_format_check(&tokens[0], parser_struct))
	{
		if (!parser_define_first_token(&tokens[0], parser_struct))
			return (0); // first argument is not valid
	}
	tokens = tokens->next;
	list = tokens;
	while (list)
	{
		if (!parser_format_check(list, parser_struct))
			parser_define_tokens(list, parser_struct);
		list = list->next;
	}
	return (parser_struct);
}
