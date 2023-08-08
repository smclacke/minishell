/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/08 14:44:05 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * @brief	assigns the tokens to a member in the parser struct:
 * 			meta, cmd, absolute path,  anything else str
 * @param	tokens passed from the lexer
 * @param	parser_struct  structure to assign each token to the correct member within parser struct
 * @return	assigns the token input to a member in the parser struct
*/
static void	*parser_define_tokens(t_parser *tokens, t_parser *parser_struct)
{
	if (!tokens)
		return (false);
	if (parser_cmp_metas(tokens))
	{
		parser_struct->meta = tokens->input;
		printf("arg->meta: %s\n", parser_struct->meta);
	}
	else if (parser_cmp_builtins(tokens))
	{	
		parser_struct->cmd = tokens->input;
		printf("arg->cmd: %s\n", parser_struct->cmd);
	}
	else if (parser_cmp_abso(tokens))
	{	
		parser_struct->abso = tokens->input;
		printf("arg->abso: %s\n", parser_struct->abso);
	}
	else if (parser_cmp_squote(tokens))
	{
		parser_struct->squote = tokens->input;
		printf("arg->squote: %s\n", parser_struct->squote);
	}
	else if (parser_cmp_dquote(tokens))
	{
		parser_struct->dquote = tokens->input;
		printf("arg->dquote: %s\n", parser_struct->dquote);
	}
	else
	{
		parser_struct->str = tokens->input;
		printf("arg->str: %s\n", parser_struct->str);
	}
	return (0);
}

void	init_parser(t_parser *parser_struct)
{
	parser_struct->str = NULL;
	parser_struct->cmd = NULL;
	parser_struct->meta = NULL;
	parser_struct->abso = NULL;
	parser_struct->squote = NULL;
	parser_struct->dquote = NULL;
	parser_struct->here_doc = NULL;
}

/**
 * @brief	Main parser function:
			Check the tokens to see which member of the parser struct they need to be sorted into
			Return the new parser_struct to the expander
 * @param	tokens t_lexer tokens passed from the lexer to be sorted by the parser
 * @return	parser_struct: all the tokens given by the lexer have been sorted into the parser struct. The first argument is checked for its validity
*/
t_parser	*parser(t_parser *tokens)
{
	t_parser	*parser_struct;
	t_parser		*list;

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
