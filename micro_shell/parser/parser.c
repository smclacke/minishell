/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:14:07 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/31 17:08:17 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * take tokens
 * take first token
 * is it cmd or << >> < >
 * yes, good, no bad
 * compare, is it buildin/redirect/here_doc?
 * t_parser->token->buildin->cmd (i.e. cat) || t_parser->token->redirect->arrow (i.e. >)
 * next token... what is it, can I work with it?
 * 
 * 
 * use quotes.c?
*/


/**
 * check validity of all the tokens
*/
// bool	micro_check_valid(t_lexer *tokens);

/**
 * add correct parts of token to defined vars in struct, parse parse parse :DD
 * e.g. export something
 * if export, attach stirng that comes after
 * par_tokens->cmd->word
 * t_parser	par_tokens->cmd = token[i];
 * token[i] = cat
*/
static void	*micro_define_tokens(t_lexer *tokens, t_parser *parser_struct)
{
	if (micro_cmp_signs(tokens))
	{
		parser_struct->sign = tokens->input;
		printf("second->sign: %s\n", parser_struct->sign);
	}
	else if (micro_cmp_builtins(tokens))
	{
		parser_struct->cmd = tokens->input;
		printf("second->cmd: %s\n", parser_struct->cmd);
	}
	else
	{
		parser_struct->str = tokens->input;
		printf("second->str: %s\n", parser_struct->str);
	}
	return (0);
}


/**
 * main parser function
 * check the first one if cmd/redirect/here_doc
 * check all other tokens if valid
 * if good, define what it is within struct, will need to do most parsing here
 * return parsed tokens to main for expander (t_parser *par_tokens)
*/
t_parser	*micro_parser(t_lexer *tokens)
{
	t_parser	*parser_struct;

	parser_struct = (t_parser *)malloc(sizeof(t_parser));
	if (!parser_struct)
		return (0);
	if (!micro_first_token(&tokens[0], parser_struct))
		return (0);
	else
	{	
		while (tokens)
		{
			// if (!micro_check_valid(token[i]))
			// 	return (0);
			// else
			micro_define_tokens(tokens, parser_struct);
			tokens = tokens->next;
		}
	}
	return (parser_struct);
}

