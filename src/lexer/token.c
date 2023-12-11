/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:39:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/11 19:31:32 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo errors
*/

/**
 * @brief	gets the index position after parsing through the
 * 			input of characters as long as there are no metas
 * 			or spaces, handling quotations, for amount_tokens()
 * @param	input from the command line
 * @param	i current index of input
 * @return	index after parsing through chars and quotes
*/
static int	quote_input(char *input, int i)
{
	char	*quote_type;

	while (input[i] && !space_or_meta(input[i]))
	{
		if (ft_isquote(input[i]))
		{
			quote_type = which_quote(&input[i]);
			i += next_quote(&input[i], *quote_type);
		}
		i++;
	}
	return (i);
}

/**
 * @brief	parses through the input and counts how many "words"
 * 			quoted strings and metas, returns the amount so that
 * 			array can be given enough space to store these tokens in
 * @param	input from the command line
 * @return	count = amount of strings that will be put into array 
 * 			and then tokenized
*/
static int	amount_tokens(char *input)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (ft_ismeta(input[i]))
		{
			if (ft_ismeta(input[i + 1]))
				i++;
			count++;
			i++;
		}
		if (input[i] && !ft_isspace(input[i]))
		{
			i = quote_input(input, i);
			count++;
		}
	}
	return (count);
}

/**
 * @brief	creates a substr to add to the 2D array
 * 			based on the length and starting position of the
 * 			input. the substr will be added as a token to the struct 
 * @param	input from the command line
 * @param	len length, desired section of input str
 * @return	token string to add to the array of tokens
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
static char	*split_tokens(char *input, int len)
{
	char	*token;

	if (!input)
		return (NULL);
	token = ft_substr(input, 0, len);
	if (!token)
		// mini_error("general: split_tokens()", E_GENERAL);
		return (0);
	input += len;
	return (token);
}

/**
 * @brief	creates an array by splitting the input string;
 * 			quotations stay intact including spaces and anything
 * 			on either side of them, everything else is split
 * 			on spaces and meta characters
 * @param	input from the command line
 * @return	array of strs to be tokenized
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
static char	**lexer_split(char *input)
{
	char	**array;
	int		i;
	int		start;
	int		len;
	int		no_tokens;

	i = 0;
	start = 0;
	len = 0;
	no_tokens = amount_tokens(input);
	array = (char **)malloc(sizeof(char *) * (no_tokens + 1));
	if (!array)
		// mini_error("malloc error: parser_split()", E_MALLOC);
		return (0);
	while (i < no_tokens)
	{
		start = start_token(input, (start + len));
		len = len_token(input, start);
		array[i] = split_tokens(&input[start], len);
		i++;
	}
	array[i] = NULL;
	return (array);
}

/**
 * @brief	creates an array of tokens from input by calling parser_split()
 * @param	input from the command line
 * @return	2D array of separated strings made from the input
 * 			ready to be passed into the parser struct list of tokens
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
char	**lexer_array(char *input)
{
	char	**array;

	array = lexer_split(input);
	if (!array)
		// mini_error("general: parse_input()", E_GENERAL);
		return (0);
	return (array);
}
