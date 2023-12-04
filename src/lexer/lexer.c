/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/04 14:47:34 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo errors
*/

/**
 * @brief	add new tokens to linked list of the t_parser struct
 * @param	parsed_input an array created but separating the input string into 
 * 			tokenizable bites
 * @return	list of tokens
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
static t_parser	*make_token_list(char **parsed_input)
{
	t_parser		*tokens;
	t_parser		*node;
	int				i;

	tokens = NULL;
	i = 0;
	if (!*parsed_input)
		return (NULL);
	while (parsed_input[i])
	{
		node = lexer_listnew(parsed_input[i]);
		if (!node)
			// mini_error("malloc error: make_token_list()", E_MALLOC);
			return (0);
		lexer_listadd_back(&tokens, node);
		i++;
	}
	free(parsed_input);
	return (tokens);
}

/**
 * @brief	takes the command line input, parses through the spaces, metas
 * 			and quotations, creating tokens
 * @param	input from the commandline
 * @return	t_parser tokens
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
t_parser	*lexer(char *input)
{
	t_parser		*tokens;
	char			**parsed_input;

	if (!input)
		return (NULL);
	parsed_input = parse_input(input);
	if (!parsed_input)
	{
		free(input);
		// mini_error("malloc error: lexer()", E_MALLOC);
		return (0);
	}
	tokens = make_token_list(parsed_input);
	if (!tokens)
		return (NULL);
	return (tokens);
}
