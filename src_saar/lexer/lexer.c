/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/01 20:39:29 by smclacke      ########   odam.nl         */
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
	t_parser		*token;
	int				len;
	int				i;

	tokens = NULL;
	i = 0;
	while (parsed_input[i])
	{
		token = lexer_listnew(parsed_input[i]);
		if (!token)
		{
			ft_free_arr(parsed_input);
			mini_error("malloc error make_token_lst2", errno);
		}
		lexer_listadd_back(&tokens, token);
		i++;
	}
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
	int			i = 0;

	parsed_input = parse_input(input);
	// free(input);
	if (!parsed_input)
		mini_error("malloc error lexer", errno);
	tokens = make_token_list(parsed_input);
	if (!tokens)
		return (NULL);
	// shelly_print_list(tokens);
	// free(tokens);
	// exit(0);
	return (tokens);
}
