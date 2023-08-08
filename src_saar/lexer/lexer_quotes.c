/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 17:07:01 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/08 23:44:00 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

static char	*make_words(char *input)
{
	int	i = 0;
	int	len;
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

static char	*handle_quotes(char *input)
{
	int			i = 0;
	int			j = 0;
	size_t		len = ft_strlen(input);
	char		*without;

	without = (char *)malloc(sizeof(char) * (len + 1));
	if (!without)
		return (NULL);
	while (input[i])
	{
		while (input[i] && lq_what_to_split(input[i]))
			i++;
		if (ft_isquote(input[i]) && lq_what_to_split(input[i - 1]))
		{
			while (input[i])
			{
				without[j] = input[i];
				printf("here: [%s]\n", input);
				printf("without: [%s]\n", without);
				// if last quote is found, return without to split_shelly
				if (input[i] && lq_what_to_split(input[i]) && !ft_isquote(input[i]))
				{
					// i NEED TO FIND THE LAST QUOTE HERE
					return (without);
					// printf("i am here\n");
					// exit(EXIT_FAILURE);
				}
				i++;
			}
		}
		// 	if (ft_isquote(input[i]) && what_to_split(input[i + 1]))
		// 		without[j] = input[i];
		// }
		// if (ft_isquote(input[i] && !what_to_split(input[i - 1])))
		// {
		// 	while (input[i] && !what_to_split(input[i]))
		// 		i--;
		// 	if (input[i] &&  what_to_split(input[i]))
		// 	{
		// 		i++;
		// 		while (input[i])
		// 		{
		// 			without[j] = input[i];
		// 			i++;
		// 		}
		// 		if (ft_isquote(input[i]) && what_to_split(input[i + 1]))
		// 			without[j] = input[i];
		// 	}
		// }
		i++;
	}
	return (without);
}

/**
 * @brief	splitting on spaces but when quote is found, create substring from first to last quote
 * @param	input from readline to tokenise
 * @return	array of split up words with quotes handled separately including spaces within quotes
*/
char	**ft_split_shelly(char *input)
{
	char	**array;
	int		i = 0;

	array = (char **)malloc(sizeof(char *) * (lq_count_words(input) + 1));
	if (!array)
		return (0);
	while (*input)
	{
		while (*input && lq_what_to_split(*input))
			input++;
		if (*input && !ft_isquote(*input))
		{
			array[i] = make_words(input);
			i++;
		}
		if (ft_isquote(*input))
		{
			array[i] = handle_quotes(input);
			i++;
		}
		while (*input && !lq_what_to_split(*input) && !ft_isquote(*input))
			input++;
	}
	array[i] = 0;
	return (array);
}
