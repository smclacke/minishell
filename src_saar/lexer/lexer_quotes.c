/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 17:07:01 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/09 23:26:52 by smclacke      ########   odam.nl         */
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

	len = quote_length(input);
	// len = ft_strlen(input);
	quotes = (char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		quotes[i] = input[i];
		i++;
	}
	quotes[i] = '\0';
	return (quotes);
}

char	**ft_split_shelly(char *input)
{
	char	**array;
	int		i = 0;

	array = (char **)malloc(sizeof(char *) * (lq_count_words(input) + 1));
	if (!array)
		return (0);
	while (*input)
	{
		while (*input && lq_what_to_split(*input) && !lq_isquote(*input)) // 
			input++;
		if (*input)
		{
			if (*input && !lq_isquote(*input))
			{
				array[i] = make_words(input);
				i++;
			}
			if (*input && lq_isquote(*input))
			{
				array[i] = make_quotes(input);
				i++;
			}
		}
		while (*input && !lq_what_to_split(*input)) //&& !lq_isquote(*input)
			input++;
	}
	array[i] = 0;
	return (array);
}
