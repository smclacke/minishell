/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/12 18:07:29 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 *        OLD VERSIONS
 * static t_parser	*make_token_list(char **parsed_input)
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

char	**lexer(char *input)
{
	char				**lexer_array;

	if (!input)
		return (NULL);
	lexer_array = lexer_array(input);
	if (!lexer_array)
	{
		free(input);
		// mini_error("malloc error: lexer()", E_MALLOC);
		return (0);
	}
	// tokens = make_token_list(lexer_array);
	// if (!tokens)
	// 	return (NULL);
	// return (tokens);
	return (lexer_array);
}
*/

char	**lexer(char *input)
{
	char	**lexer_array;

	if (!input)
		return (NULL);
	lexer_array = 
}
