/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:39:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/02 19:20:10 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @brief	create a substr to add to the 2D array
 * 			based on the length and starting position of the
 * 			input. the substr will be added as a token to the struct 
 * @param	input from the command line
 * @param	len length, decired section of input str
 * @return	token string to add to the array of tokens
*/
static char	*split_tokens(char *input, int len)
{
	char	*token;

	token = ft_substr(input, 0, len);
	if (!token)
		return (NULL);
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
*/
static char	**parser_split(char *input)
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
		return (ft_free_arr(array), NULL);
	while (i < no_tokens)
	{
		start = start_token(input, (start + len));
		printf("start = %d\n", start);
		len = len_token(input, start);
		printf("len = %i\n", len);
		array[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!array[i])
			return (NULL);
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
 * 			ready to be parsed into the parser struct list of tokens
*/
char	**parse_input(char *input)
{
	char	**array;

	array = parser_split(input);
	if (!array)
		return (NULL);
	return (array);
}
