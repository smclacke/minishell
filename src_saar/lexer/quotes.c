/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 17:07:01 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/20 22:14:59 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

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
		return (0); // ERROR HERE and quit 
	return (i);
}

/**
 * check_quotes()
 * find quotes, return the string from first to last quote (not necessary the actual closing quote...
 * but I'll do that in the parser)
 * if unclosed, throw error
*/
char	*check_quotes(char *input)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = ft_strlen(input);
	while (len > 0)
	{
		if (ft_isquote(input[len]))
		{
			ret = ft_substr(input, i, len + 1);
			if (!ret)
				return (0);
			return (ret);
		}
		--len;
	}
	return (0);
}
