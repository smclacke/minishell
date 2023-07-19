/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 16:19:44 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/19 16:27:50 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * different kind of split, finding main elements of the input to split, else just on whitespace
*/
static int	what_to_split(char *input)
{
	int	i = 0;

	while (input[i])
	{
		if (input[i] == '\"' && closed_quotes(input))
			return (DQUOTE);
	}
	return (0);
}

/**
 * make a 2D array of the input, split anything in quotes into one string, redirects and delimiters
 * into tokens and everything else via spaces into separate strings, give to the lexer to make 
 * tokens and pass token list back to main
*/
char	**split_input(char *input)
{
	char	**array = NULL;
	char	*quote_str;
	int		words = 0;
	int		i = 0;
	
	while (input[i])
	{
		if (what_to_split(input[i]) == DQUOTE || what_to_split(input[i]) == SQUOTE)
		{
			quote_str = check_quotes(input);
			if (!quote_str)
				return (0);
			else
			{	
				array[words] = quote_str;
				words++;
			}
		}
		// if dollar... but this is gunna be a long function, HOW TO WRITE THIS IS IN A NOT STUPID WAY
		i++;
	}
	return (array);
}
