/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/02 19:18:47 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @brief	once input has been parsed, quoted segments separated 
 * 			and spaces removed from the rest of the input, 
 * 			iterate through the array creating substrings 
 * 			to put into token_str variable.
 * 			Node in a t_lexer list are created and added to the token_list 
 * 			which is returned to the parser function to be passed to the parser
 * @param	parsed_input an array created but separating the input string into 
 * 			tokenizable bites
 * @return	newly made t_lexer token_list
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
			return (0);
		token = lexer_listnew(token_str);
		if (!token)
			return (0);
		lexer_listadd_back(&tokens, token);
		i++;
	}
	return (tokens);
}

/**
 * @brief	takes the command line input, parses through the spaces 
 * 			outside quotations and creates
 * 			t_lexer tokens to pass to the parser. In the case of quotations,
 * 			spaces must be kept and checked
 * 			for their validity, so if a quotation is encountered, take the 
 * 			end of the string and iterate through to find the last quotation,
 * 			all of this input is tokenized and then separated and validated
 * 			in the parser. 
 * @param	input from the commandline
 * @return	t_lexer token_list to pass to the parser
*/
t_parser	*lexer(char *input)
{
	t_parser		*tokens;
	char			**parsed_input;

	// parsed_input = NULL;
	tokens = (t_parser *)malloc(sizeof(t_parser));
	if (!tokens)
		return (0);
	ft_bzero(tokens, sizeof(t_parser));
	parsed_input = parse_input(input);
	if (!parsed_input)
		return (0);
	// free(input);
	tokens = make_token_list(parsed_input);
	if (!tokens)
		return (0);
	// free(parsed_input);
	return (tokens);
}
