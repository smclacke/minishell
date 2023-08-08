/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_quote_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/08 23:30:05 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/08 23:35:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

int	lq_what_to_split(char c)
{
	if (c == 0 || c == 32 || c == 9 || c == 10)
		return (1);
	return (0);
}

int	lq_count_words(char *input)
{
	int	i = 0;
	int	count = 0;
	
	while (input[i])
	{
		while (input[i] && lq_what_to_split(input[i]))
			i++;
		if (input[i])
			count++;
		while (input[i] && !lq_what_to_split(input[i]))
			i++;
	}
	return (count);
}

int	lq_word_length(char *input)
{
	int	i = 0;

	while (input[i] && !lq_what_to_split(input[i]))
		i++;
	return (i);
}
