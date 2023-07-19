/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 16:19:44 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/19 19:41:13 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * while input is none of these things and not a space, just read through, else, find out what it is
*/
static int	what_to_split(char *input)
{
	int	i = 0;

	while (input[i])
	{
		if (input[i] == '\"' && closed_quotes(input))
			return (DQUOTE);
		if (input[i] == '\'' && closed_quotes(input))
			return (SQUOTE);
		if (input[i] == '$')
			return (DOLLAR);
		if (input[i] == '>' && input[i + 1] == '>')
			return (MOREMORE);
		else if (input[i] == '>')
			return (MORE);
		if (input[i] == '<' && input[i + 1] == '<')
			return (LESSLESS);
		else if (input[i] == '<')
			return (LESS);
		if (input[i] == '|')
			return (PIPE); 
		i++;
	}
	return (0);
}

// char	*what_are_you(char *input)
// {
	
// }

/**
 * make a 2D array of the input, split anything in quotes into one string, redirects and delimiters
 * into tokens and everything else via spaces into separate strings, give to the lexer to make 
 * tokens and pass token list back to main
*/
char	**split_input(char *input)
{
	char	**array = NULL;
	char	*word_str = NULL;
	char	*sign_str = NULL;
	// int		words = 0;
	int		i = 0; // input index
	int		w = 0; // word strings no signs
	int		s = 0; // sign strings
	
	while (input[i])
	{
		if (!what_to_split(input) && !ft_isspace(input[i]))
		{	
			word_str[w] = input[i];
			i++;
			w++;
		}
		if (what_to_split(input[i]))
			sign_str[s] = what_are_you(input[i]);
		// array[] make the array somehow in order of the things I've just found
		// if (what_to_split(input[i]) == DQUOTE || what_to_split(input[i]) == SQUOTE)
		// {
		// 	quote_str = check_quotes(input);
		// 	if (!quote_str)
		// 		return (0);
		// 	else
		// 	{	
		// 		array[words] = quote_str;
		// 		words++;
		// 	}
		// }
		// if (what_to_split(input[i] == DOLLAR))
		// {
		// 	while (input[i + 1] && !ft_isspace(input[i + 1]))
		// 	{
		// 		i++;
		// 		count++;
		// 	}
		// 	count -= i;
		// 	array[words] = input[count - 1];
		// 	words++;
		// }
		// // if dollar... etc finding all signs BUT ORDER???, save the indexs so I'm 
		// // tokenizing in order they appear, FIND A BETTER WAY OF DOING THIS
		// words++;
		// }
		i++;
	}
	return (array);
}
