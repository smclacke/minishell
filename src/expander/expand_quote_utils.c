/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_quote_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/28 16:34:53 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/07 19:29:49 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

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

/**
 * just ignore this func....
 * don't mind me....
*/
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
