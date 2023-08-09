/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 17:07:01 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/09 17:08:40 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

static char	*make_words(char *input)
{
	int		i = 0;
	int		len;
	char	*words;

	len = lq_word_length(input);
	words = (char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		words[i] = input[i];
		i++;
	}
	words[i] = '\0';
	return (words);
}

static char	*make_quotes(char *input)
{
	int		i = 0;
	int		len;
	char	*quotes;

	// len = quote_length(input);
	len = ft_strlen(input);
	quotes = (char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		quotes[i] = input[i];
		i++;
	}
	quotes[i] = '\0';
	return (quotes);
}

/**
 * @brief	splitting on spaces but when quote is found, create substring from first to last quote
 * @param	input from readline to tokenise
 * @return	array of split up words with quotes handled separately including spaces within quotes
*/
// char	**ft_split_shelly(char *input)
// {
// 	char	**array;
// 	int		i = 0;

// 	array = (char **)malloc(sizeof(char *) * (lq_count_words(input) + 1));
// 	if (!array)
// 		return (0);
// 	while (*input)
// 	{
// 		while (*input && lq_what_to_split(*input))
// 			input++;
// 		if (*input && !ft_isquote(*input))
// 		{
// 			array[i] = make_words(input);
// 			i++;
// 		}
// 		if (ft_isquote(*input))
// 		{
// 			array[i] = make_quotes(input);
// 			i++;
// 		}
// 		while (*input && !lq_what_to_split(*input) && !ft_isquote(*input))
// 			input++;
// 	}
// 	array[i] = 0;
// 	return (array);
// }

char	**ft_split_shelly(char *input)
{
	char	**array;
	int		i = 0;
	int		j = 0;

	array = (char **)malloc(sizeof(char *) * (lq_count_words(input) + 1));
	if (!array)
		return (0);
	while (*input)
	{
		while (*input && lq_what_to_split(*input) && !ft_isquote(*input))
		{
			input++;
			j++;
		}
		if (*input && !ft_isquote(*input))
		{
			array[i] = make_words(input);
			i++;
		}
		while (*input && !lq_what_to_split(*input))
			input++;
	}
	array[i] = 0;
	return (array);
}
