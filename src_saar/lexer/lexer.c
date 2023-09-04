/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/04 22:38:05 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"


/**
 * @brief	takes the input string from the command line, iterates through it. While there
 * 			are no quotations, the string is split on spaces. If a quotation is encountered, 
 * 			the last quotation in the string is found and that segment is made into a separate
 * 			part of the array. 
 * @param	input input from the command line
 * @return	2D array of separated strings made from the input, ready to be tokenized
*/
static char	**parse_input(char *input)
{
	char	**array = NULL;
	// int		i = 0;

		 // WE MUST SEPARATE METAS,,,,,,,,, OUI?
	// split on spaces, split on metas but add metas to token array
	// if quotes, split those apart keep them totally intact
	// if (shelly_check_quotes(input))
	// {
	// 	array = ft_split_shelly(input); // this needs to work at some point in the future
	// 	if (!array)
	// 		return (NULL);
	// }
	// else
	// {
		array = ft_split(input, ' ');
		if (!array)
			return (NULL);
		// while (array[i])
		// {
			
		// }
	// }
	return (array);
}

/**
 * @brief	once input has been parsed, quoted segments separated and spaces removed from the rest
 * 			of the input, iterate through the array creating substrings to put into token_str variable.
 * 			Node in a t_lexer list are created and added to the token_list which is returned to the parser
 * 			function to be passed to the parser.  
 * @param	parsed_input an array created but separating the input string into tokenizable bites
 * @return	newly made t_lexer token_list
*/
static t_parser	*make_token_list(char **parsed_input)
{
	t_parser		*tokens = NULL;
	t_parser		*token;
	char			*token_str;
	int				len;
	int				i = 0;

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
 * @brief	takes the command line input, parses through the spaces outside quotations and creates
 * 			t_lexer tokens to pass to the parser. In the case of quotations, spaces must be kept and checked
 * 			for their validity, so if a quotation is encountered, take the end of the string and iterate
 * 			through to find the last quotation, all of this input is tokenized and then separated and validated
 * 			in the parser. 
 * @param	input from the commandline
 * @return	t_lexer token_list to pass to the parser
*/
t_parser	*lexer(char *input)
{
	t_parser		*tokens;
	char			**parsed_input = NULL;
	int				i;

	i  = 0;
	tokens = (t_parser *)malloc(sizeof(t_parser));
	if (!tokens)
		return (0);
	init_parser(tokens);
	while (input[i])
	{
		parsed_input = parse_input(input);
		i++;
	}
	i = 0;
	if (!parsed_input)
		return (0);
	tokens = make_token_list(parsed_input);
	if (!tokens)
		return (0);
	return (tokens);
}
