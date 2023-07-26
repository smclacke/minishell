/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:14:07 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/26 17:19:47 by smclacke      ########   odam.nl         */
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
 * use this quotes.c?
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
// t_parser	*micro_define_tokens(t_lexer *tokens);



/**
 * main parser function
 * check the first one if cmd/redirect/here_doc
 * check all other tokens if valid
 * if good, define what it is within struct, will need to do most parsing here
 * return parsed tokens to main for expander (t_parser *par_tokens)
*/
int	micro_parser(t_lexer *tokens)
{
	// t_parser	*par_tokens = NULL;
	// int	i = 0;

	if (micro_first_token(&tokens[0]))
		return (0);
	else
	{
		printf("valid first token: ");
		micro_ft_print_tokens(&tokens[0]);
	}
	// else
	// {
	// 	while (tokens[i])
	// 	{
	// 		if (!micro_check_valid(token[i]))
	// 			return (0);
	// 		else
	// 			par_tokens = micro_define_tokens(tokens[i]);
	// 	}
	// 	i++;
	// }
	// return (par_tokens);
	return (0);
}

