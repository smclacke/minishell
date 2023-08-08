/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/08 15:07:31 by smclacke      ########   odam.nl         */
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
static void	*parser_define_tokens(t_parser *tokens)
{
	if (!tokens)
		return (false);
	if (parser_cmp_metas(tokens))
	{
		tokens->meta = tokens->input;
		printf("arg->meta: %s\n", tokens->meta);
	}
	else if (parser_cmp_builtins(tokens))
	{	
		tokens->cmd = tokens->input;
		printf("arg->cmd: %s\n", tokens->cmd);
	}
	else if (parser_cmp_abso(tokens))
	{	
		tokens->abso = tokens->input;
		printf("arg->abso: %s\n", tokens->abso);
	}
	else if (parser_cmp_squote(tokens))
	{
		tokens->squote = tokens->input;
		printf("arg->squote: %s\n", tokens->squote);
	}
	else if (parser_cmp_dquote(tokens))
	{
		tokens->dquote = tokens->input;
		printf("arg->dquote: %s\n", tokens->dquote);
	}
	else
	{
		tokens->str = tokens->input;
		printf("arg->str: %s\n", tokens->str);
	}
	return (0);
}

void	init_parser(t_parser *tokens)
{
	
	tokens->str = NULL;
	tokens->cmd = NULL;
	tokens->meta = NULL;
	tokens->abso = NULL;
	tokens->squote = NULL;
	tokens->dquote = NULL;
	tokens->here_doc = NULL;
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
	t_parser		*list;

	init_parser(tokens);
	list = tokens;
	while (list)
	{
		parser_define_tokens(list);
		list = list->next;
	}
	return (tokens);
}
