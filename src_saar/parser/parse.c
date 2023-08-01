/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/01 17:12:47 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * @brief	Checking whether the first arg token is valid:
 * 			$, <<. >>, <, >, buildin cmd, or absolute path. 
 * 			~ Add check for other cmds somehow ~
 * 			The rest of the arg tokens are checked in define_token
 * @param	tokens first arg token passed from the lexer to the parser
 * @param	parser_struct  structure to assign each token to the correct type within parser struct
 * @return	bool: true/false 1/0
*/
static bool	parser_define_first_token(t_lexer *tokens, t_parser  *parser_struct)
{
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
 * @brief	assigns the tokens to a type in the parser struct:
 * 			sign, pipe, builtin, absolute path or str
 * @param	tokens passed from the lexer, first token has already been handled in parser_define_first_token()
 * @param	parser_struct  structure to assign each token to the correct type within parser struct
 * @return	
*/
static void	*parser_define_tokens(t_lexer *tokens, t_parser *parser_struct)
{
	if (parser_cmp_signs(tokens))
	{
		parser_struct->sign = tokens->input;
		printf("second->sign: %s\n", parser_struct->sign);
	}
	else if (ft_strnstr(tokens->input, "|", 1) == 0)
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
 * put input into tmp, remove quotes and make lowercase, test against builtins, if yes, return tmp since valid
 * 	else return original
 * @brief
 * @param
 * @return 
*/
static bool	parser_format_check(t_lexer *tokens, t_parser *parser_struct)
{
	ft_lower_str(tokens->input);
	if (parser_check_quotes(tokens))
	{
		tokens->input = remove_quotes(tokens);
		if (!tokens->input)
			return (0);
		if (parser_cmp_builtins(tokens))
		{
			parser_struct->cmd = tokens->input;
			printf("first->cmd: %s\n", parser_struct->cmd);
			return (true);
		}
	}
	else
		if (parser_cmp(tokens, parser_struct))
			return (true);
	return (false);
}

/**
 * main parser function
 * check the first one if cmd/redirect/here_doc
 * check all other tokens if valid
 * if good, define what it is within struct, will need to do most parsing here
 * return parsed tokens to main for expander
 * 
 * i want a check tokens function that will do the same as first_token: take input, 
 * put into temp, remove quotes, make lowcase, check if buildin, if yes, pass as cmd, else, continue with
 * original input
*/
t_parser	*parser(t_lexer *tokens)
{
	t_parser	*parser_struct;
	t_lexer		*list;

	parser_struct = (t_parser *)malloc(sizeof(t_parser));
	if (!parser_struct)
		return (0);
	// check format
	if (!parser_define_first_token(&tokens[0], parser_struct))
		return (0);
	tokens = tokens->next;
	list = tokens;
	while (list)
	{
		parser_define_tokens(list, parser_struct);
		list = list->next;
	}
	return (parser_struct);
}



// UNNCESSARY CHECK ALL TOKENS WITH A SEPARATE FUNCTION IN PARSER() AND THEN JUST DEFINE WITH THE SPECIFIC TWO FUNCS IN PARSER()
// /**
//  * @brief	compare the first token to cmds and valid signs
//  * 			// will also need to find a way to allow first token to be non-built in command...
//  * @param	tokens first arg token passed from the lexer to the parser
//  * @param	parser_struct  structure to assign each token to the correct type
//  * @return	bool: true/false 1/0
// */
// static bool	parser_first_token(t_lexer *tokens, t_parser *parser_struct)
// {
// 	ft_lower_str(tokens->input);
// 	if (parser_check_quotes(tokens))
// 	{
// 		tokens->input = remove_quotes(tokens);
// 		if (!tokens->input)
// 			return (0);
// 		if (parser_cmp_builtins(tokens))
// 		{
// 			parser_struct->cmd = tokens->input;
// 			printf("first->cmd: %s\n", parser_struct->cmd);
// 			return (true);
// 		}
// 	}
// 	else
// 		if (parser_cmp(tokens, parser_struct))
// 			return (true);
// 	return (false);
// }
