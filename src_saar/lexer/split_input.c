/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 16:19:44 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/19 18:54:33 by smclacke      ########   odam.nl         */
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
		else if (input[i] == '\"' && !closed_quotes(input))
			return (127); // need syntax error here
		else if (input[i] == '\'' && close_quotes(input))
			return (SQUOTE);
		else if (input[i] == '\'' && !closed_quotes(input))
			return (127); // need syntax error here
		else if (input[i] == '$')
			return (DOLLAR);
		else if (input[i] == '>')
			return (MORE);
		else if (input[i] == '<')
			return (LESS);
		else if (input[i] == '>' && input[i + 1] == '>')
			return (MOREMORE);
		else if (input[i] == '<' && input[i + 1] == '<')
			return (LESSLESS);
		else if (input[i] == '|')
			return (PIPE);
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
	int		count = 0;
	
	while (input[i])
	{
		while (!what_to_split(input[i]))
		{	
			array[words] = ft_split(input, ' ');
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
			if (what_to_split(input[i] == DOLLAR))
			{
				while (input[i + 1] && !ft_isspace(input[i + 1]))
				{
					i++;
					count++;
				}
				count -= i;
				array[words] = input[count - 1];
				worrds++;
			}
		// if dollar... etc finding all signs BUT ORDER???, save the indexs so I'm 
		// tokenizing in order they appear, FIND A BETTER WAY OF DOING THIS
			words++;
		}
		i++;
	}
	return (array);
}
