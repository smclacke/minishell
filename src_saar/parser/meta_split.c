/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_split.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/03 19:43:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/03 21:02:21 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

int	ms_word_count(t_parser *tokens)
{
	int		i = 0;
	int		count = 0;

	while (tokens[i])
	{
		while (tokens[i] && !is_redirect(tokens[i]))
			i++;
		if (tokens[i])
			count++;
		while (tokens[i] && is_redirect(tokens[i]))
			i++;
	}
	return (count);
}

int	ms_word_len(t_parser *tokens)
{
	int	i = 0;

	while (tokens[i] && !is_redirect(tokens[i]))
		i++;
	return (i);
}

t_parser	*ms_make_words(t_parser *tokens)
{
	t_parser	*words;
	int		i = 0;
	int		len = ms_word_len(tokens);

	words = (t_parser *)malloc(sizeof(t_parser) * len + 1);
	while (i < len)
	{
		words[i] = tokens[i];
		i++;
	}
	words[i] = '\0';
	return (words);
}

t_parser	**meta_split(t_parser *tokens)
{
	t_parser	**array;
	int		i = 0;
	
	array = (t_parser **)malloc(sizeof(t_parser *) * ms_word_count(tokens) + 1);
	while (*tokens)
	{
		while (*tokens && !is_redirect(tokens))
			tokens++;
		if (*tokens)
		{
			array[i] = ms_make_words(tokens);
			i++;
		}
		while (*tokens && is_redirect(tokens))
			tokens++;
	}
	array[i] = 0;
	return (array);
}
