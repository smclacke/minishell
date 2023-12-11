/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/11 19:43:22 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"


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
