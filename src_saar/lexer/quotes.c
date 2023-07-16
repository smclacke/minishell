/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 17:07:01 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/16 16:39:12 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * are there quotes? are there matching quotes? are they closed? cool, take everything and tokenize it
*/

/**
 * closed_quotes()
 * check if double or single, count amount for each, check if divisable by 2 (thus closed)
 * separate check for double and single since 1x double + 1x single must throw an error
*/
int	closed_quotes(char *input)
{
	int	i;
	int	count_double;
	int	count_single;

	i = 0;
	count_double = 0;
	count_single = 0;
	while (input[i])
	{
		if (ft_isdouble_q(input[i]))
			count_double++;
		i++;
	}
	i = 0;
	while (input[i])
	{
		if (ft_issingle_q(input[i]))
			count_single++;
		i++;
	}
	if ((count_double % 2) != 0 || (count_single % 2) != 0)
		return (0);
	return (i);
}

/**
 * check_quotes()
 * find quotes
 * if unclosed, throw error
*/
char	*check_quotes(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (ft_isquote(input[i]))
		{
			if (!closed_quotes(input))
				return (0);
		}
		i++;
	}
	return (input);
}
