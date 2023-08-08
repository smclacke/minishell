/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:14:07 by smclacke      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/08/03 15:53:57 by smclacke      ########   odam.nl         */
=======
/*   Updated: 2023/08/03 15:55:25 by smclacke      ########   odam.nl         */
>>>>>>> sarah
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

<<<<<<< HEAD
// DONT REMOVE CAPS OR QUOTES, JUST MAKE THE BEST TOKENS I CAN AND EXECVE AND PATH CMP WILL DO THE REST
=======
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
		printf("first->sign:	~: %s\n", parser_struct->sign);
		return (true);
	}
	else if (parser_cmp_builtins(tokens))
	{	
		parser_struct->cmd = tokens->input;
		printf("first->cmd:		~: %s\n", parser_struct->cmd);
		return (true);
	}
	else if (parser_cmp_abso(tokens))
	{
		parser_struct->abso = tokens->input; // will at some point need to validate the paths...
		printf("first->abso:	~: %s\n", parser_struct->abso);
		return (true);	
	}
	return (false);
}
>>>>>>> sarah

/**
 * @brief	assigns the tokens to a member in the parser struct:
 * 			meta, cmd, absolute path or anything else str
 * @param	tokens passed from the lexer
 * @param	parser_struct  structure to assign each token to the correct member within parser struct
 * @return	assigns the token input to a member in the parser struct
*/
static void	*parser_define_tokens(t_lexer *tokens, t_parser *parser_struct)
{
	if (!tokens)
		return (false);
	if (parser_cmp_metas(tokens))
	{
		parser_struct->meta = tokens->input;
		printf("arg->meta:	~: %s\n", parser_struct->meta);
	}
	else if (parser_cmp_builtins(tokens))
	{	
		parser_struct->cmd = tokens->input;
		printf("arg->cmd:	~: %s\n", parser_struct->cmd);
	}
	else if (parser_cmp_abso(tokens))
	{	
		parser_struct->abso = tokens->input;
		printf("arg->abso:	~: %s\n", parser_struct->abso);
	}
	else
	{
		parser_struct->str = tokens->input;
		printf("arg->str:	~: %s\n", parser_struct->str);
	}
	return (0);
}

void	init_parser(t_parser *parser_struct)
{
	parser_struct->str = NULL;
	parser_struct->cmd = NULL;
	parser_struct->meta = NULL;
	parser_struct->abso = NULL;
}

/**
 * @brief	Main parser function:
			Check the tokens to see which member of the parser struct they need to be sorted into
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
	list = tokens;
	while (list)
	{
		parser_define_tokens(list, parser_struct);
		list = list->next;
	}
	return (parser_struct);
}