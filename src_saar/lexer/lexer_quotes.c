/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 17:07:01 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/08 21:47:12 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

// bool	parser_check_quotes(char *tokens) // no different than ft_isquote right?
// {
// 	char	*tmp;
// 	int		i = 0;
	
// 	tmp = tokens;
// 	while (tmp[i])
// 	{
// 		if (ft_isquote(tmp[i]))
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

int	what_to_split(char c)
{
	if (c == 0 || c == 32 || c == 9 || c == 10)
		return (1);
	return (0);
}

int	count_words(char *input)
{
	int	i = 0;
	int	count = 0;
	
	while (input[i])
	{
		while (input[i] && what_to_split(input[i]))
			i++;
		if (input[i])
			count++;
		while (input[i] && !what_to_split(input[i]))
			i++;
	}
	return (count);
}

int	word_length(char *input)
{
	int	i = 0;

	while (input[i] && !what_to_split(input[i]))
		i++;
	return (i);
}

char	*make_words(char *input)
{
	int	i = 0;
	int	len;
	char	*words;

	len = word_length(input);
	words = (char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		words[i] = input[i];
		i++;
	}
	words[i] = '\0';
	return (words);
}

/**
 * @brief	splitting on spaces but when quote is found, create substring from first to last quote
 * @param	input from readline to tokenise
 * @param	c will be spaces, need to get rid of them all except for within quotes
 * @return	array of split up words with quotes handled separately including spaces within quotes
*/
char	**ft_split_shelly(char *input)
{
	char	**array;
	int		i = 0;

	if (!input)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (count_words(input) + 1));
	if (!array)
		return (0);
	while (*input)
	{
		while (*input && what_to_split(*input) && !ft_isquote(*input))
			input++;
		if (*input && !ft_isquote(*input))
		{
			array[i] = make_words(input);
			i++;
		}
		while (*input && !what_to_split(*input) && !ft_isquote(*input))
			input++;
		// if (*input && ft_isquote(*input))
	}
	array[i] = 0;
	return (array);
}
