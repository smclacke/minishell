/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/07 18:56:34 by smclacke      ########   odam.nl         */
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
			mini_error("malloc error: make_token_list()", E_MALLOC);
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
		mini_error("malloc error: lexer()", E_MALLOC);
	}
	tokens = make_token_list(parsed_input);
	if (!tokens)
		return (NULL);
	return (tokens);
}
