/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 16:19:44 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/21 13:56:08 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * returns correct int to make tokens from the signs, but...
 * >> 
 * token: >>
 * token: >
*/
int	sign_tokens(char *input)
{
	int	i = 0;

	while (input[i])
	{
		if (ft_strcmp(&input[i], "$") == 0)
			return (DOLLAR);
		else if (ft_strcmp(&input[i], ">>") == 0)	
			return (MOREMORE);
		else if (ft_strcmp(&input[i], ">") == 0)
			return (MORE);
		else if (ft_strcmp(&input[i], "<<") == 0)
			return (LESSLESS);
		else if (ft_strcmp(&input[i], "<") == 0)
			return (LESS);
		else if (ft_strcmp(&input[i], "|") == 0)
			return (PIPE); 
		i++;
	}
	return (0);
}

/**
 * get full quoted string
*/
char	*quote_tokens(char *input)
{
	char	*quote_strs = NULL;
	int		i = 0;

	while (input[i])
	{
		if (input[i] == '\'' && closed_quotes(&input[i]))
			quote_strs = &input[i + closed_quotes(&input[i])];
		if (input[i] == '\"' && closed_quotes(&input[i]))
			quote_strs = &input[i + closed_quotes(&input[i])];
		i++;
	}
	return (quote_strs);
}

/**
 * make a 2D array of the input, split anything in quotes into one string, redirects and delimiters
 * into tokens and everything else via spaces into separate strings, give to the lexer to make 
 * tokens and pass token list back to main
*/
char	**split_input(char *input)
{
	char	**array = NULL;
	char	*quotes;
	int		i = 0;
	
	array = (char **)malloc(sizeof(char *) * (ft_strlen(input) + 1));
	if (!array)
		return (0);
	while (input[i])
	{
		if (sign_tokens(&input[i]))
			array[i] = &input[i];
		if (ft_isquote(input[i]))
			quotes = quote_tokens(&input[i]);
		// rest ... make_words, then add everything to array
		i++;
	}
	array[i] = 0;
	return (array);
}
