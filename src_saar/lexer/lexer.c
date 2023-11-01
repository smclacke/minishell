/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/01 16:14:41 by smclacke      ########   odam.nl         */
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
	char			*token_str;
	int				len;
	int				i;

	tokens = NULL;
	i = 0;
	while (parsed_input[i])
	{
		len = ft_strlen(parsed_input[i]);
		token_str = ft_substr(parsed_input[i], 0, len + 1);
		if (!token_str)
			mini_error("malloc error make_token_lst1", errno);
		token = lexer_listnew(token_str);
		if (!token)
			mini_error("malloc error make_token_lst2", errno);
		lexer_listadd_back(&tokens, token);
		i++;
	}
	ft_free_arr(parsed_input);
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

	parsed_input = parse_input(input);
	if (!parsed_input)
		mini_error("malloc error lexer", errno);
	tokens = make_token_list(parsed_input);
	if (!tokens)
		return (NULL);
	return (tokens);
}
