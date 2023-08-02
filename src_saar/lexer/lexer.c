/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:37:14 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/02 12:48:12 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * after splitting correctly on quotes and spaces, take quote tokens, parse them in lexer
 * make new tokens out of them so they can be handled easier with my current parser system
 * could already put them in lexer struct as token->quote str, token->quoted_cmd etc, and in parser
 * just check if the token has any specification and if so, put that in parser struct
*/

/**
 * need to check for flags somewhere!
*/

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
	int		i = 0;
	// int		j = ft_strlen(input);
	// int		k = 0;

	while (input[i])
	{
		if (input[i] && !ft_isquote(input[i]))
		{
			array = ft_split(input, ' ');
		}
		if (ft_isquote(input[i]))
		{
			printf("I found a quote\n");
			// while (input[j] && i < j)
			// {
			// 	if (ft_isquote(input[j]))
			// 	{
			// 		while (input[j - i] && i < j)
			// 		array[k] = &input[i];
			// 		i++;
			// 	}
			// 	j--;
			// }
		}
		i++;
	}
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
static t_lexer	*make_token_list(char **parsed_input)
{
	t_lexer		*token_list = NULL;
	t_lexer		*token;
	char		*token_str;
	int			len;
	int			i = 0;

	while (parsed_input[i])
	{
		len = ft_strlen(parsed_input[i]);
		token_str = ft_substr(parsed_input[i], 0, len + 1);
		if (!token_str)
			return (0);
		token = lexer_listnew(token_str);
		if (!token)
			return (0);
		lexer_listadd_back(&token_list, token);
		i++;
	}
	return (token_list);
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
t_lexer	*lexer(char *input)
{
	t_lexer		*token_list;
	char		**parsed_input = NULL;
	int			i;

	i  = 0;
	while (input[i])
	{
		parsed_input = parse_input(input);
		i++;
	}
	i = 0;
	if (!parsed_input)
		return (0);
	token_list = make_token_list(parsed_input);
	if (!token_list)
		return (0);
	return (token_list);
}
