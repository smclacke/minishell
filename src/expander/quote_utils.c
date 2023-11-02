/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/28 16:34:53 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/31 19:42:31 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @brief	are there any quotes?
*/
int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	increment(int *len, int *i)
{
	(*len)++;
	(*i)++;
}

/**
 * @brief	are there spaces inside the quotation?
 * 			cmds are invalid if this is true
*/
int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	quote_type(int str)
{
	if (str == '\'')
		return ('\'');
	else if (str == '\"')
		return ('\"');
	return (0);
}

/**
 * @brief	length of string without the quotes that are going to be removed
 * 			encounter a quote, find matching, remove both, keep everything
 * 			inside those quotes intact
*/
int	len_quotes(char *str)
{
	int	i;
	int	q;
	int	len;

	i = 0;
	q = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] && !ft_isquote(str[i]))
			increment(&len, &i);
		if (ft_isquote(str[i]))
		{
			q = quote_type(str[i]);
			i++;
			while (str[i] && str[i] != q)
				increment(&len, &i);
		}
		if (ft_isquote(str[i]) && str[i] == q)
			i++;
	}
	return (len);
}
