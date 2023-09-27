/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:39:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/27 20:31:38 by smclacke      ########   odam.nl         */
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
 * @brief	split on spaces, separate metas into their own string
 * 			if there are quotations, take everything inside 
 * 			(including spaces), add anything from either side
 * 			that isn't separated by spaces
 * 			create an array to tokenize and parse
 * @param	input from the command line
 * @param	no_tokens number of tokens needed and therefore 
 * 			amount of space needed in the array
 * @return	array of tokens which will be passed to the parser
 */
static char	**parser_split(char *input, int no_tokens)
{
	char	**array;
	int		start;
	int		len;
	int		i;

	array = NULL;
	start = 0;
	len = 0;
	i = 0;
	while (i < no_tokens)
	{
		printf("no_tokens = %i\n", no_tokens);
		start = start_token(input, (start + len));
		printf("start_token = %i\n", start);
		len = len_token(input, start);
		printf("len_token = %i\n", len);
		array[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!array[i])
			return (NULL);
		printf("i am here\n");
		array[i] = split_tokens(&input[start], len);
		i++;
	}
	return (array);
}

/**
 * @brief	if there's quotation and/or meta char, need to find them and
 * 			split them accordingly. Otherwise, just split on spaces
 * @param	input from the command line
 * @return	1 yes there's a meta and/or quotation. 0 false
*/
static int	check_split(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_isquote(input[i]) || ft_ismeta(input[i]))
			return (1);
		i++;
	}
	return (0);
}

// /**
//  * @brief	takes the input string from the command line, 
//  * 			iterates through it. If there are quoations and/or meta chars,
//  * 			input is split on metas, quotations and spaces.
//  * 			otherwise only spaces
//  * @param	input input from the command line
//  * @return	2D array of separated strings made from the input, 
//  * 			ready to be tokenized into the parser struct list of tokens
// */
char	**parse_input(char *input)
{
	char	**array;
	int		no_tokens;

	array = NULL;
	no_tokens = 0;
	printf("input = %s\n", input);
	if (check_split(input))
	{
		no_tokens = amount_tokens(input);
		array = (char **)malloc(sizeof(char *) * (no_tokens + 1));
		if (!array)
			return (NULL);
		array = parser_split(input, no_tokens);
		if (!array)
			return (NULL);
	}
	else
		array = ft_split(input, ' ');
	if (!array)
		return (NULL);
	return (array);
}

// OLD
// char	**parse_input(char *input)
// {
// 	char	**array = NULL;
// 	int		no_tokens = 0;
// 	int		start = 0;
// 	int		len = 0;
// 	int		i = 0;

// 	if (check_split(input))
// 	{
// 		no_tokens = amount_tokens(input);
// 		printf("no_tokens: %i\n", no_tokens);
// 		array = (char **)malloc(sizeof(char *) * (no_tokens + 1));
// 		if (!array)
// 			return (NULL);
// 		while (i < no_tokens)
// 		{
// 			start = start_token(input, (start + len));
// 			printf("start = %i\n", start);
// 			len = len_token(input, start);
// 			array[i] = (char *)malloc(sizeof(char) * (len + 1));
// 			if (!array)
// 				return (NULL);
// 			array[i] = split_tokens(&input[start], len);
// 			i++;
// 		}
// 		array[i] = NULL;
// 	}
// 	else
// 		array = ft_split(input, ' ');
// 	if (!array)
// 		return (NULL);
// 	return (array);
// }
