/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pot_use.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/08 23:30:05 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/12 18:15:26 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"



int	lq_what_to_split(char c)
{
	return (c == 0 || c == 32 || c == 9 || c == 10);
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

int	quote_len(char *input)
{
	int	i = 0;

	while (input[i])
	{
		if (which_quote(input[i]) == 1)
		{
			while (input[i])
			{
				i++;
				if (which_quote(input[i] == 1))
				{
					return (i);
				}
			}
		}
		else if (which_quote(input[i]) == 2)
		{
			while (input[i])
			{
				i++;
				if (which_quote(input[i] == 2))
					return (i);
			}
		}
		i++;
	}
	return (0);
}
