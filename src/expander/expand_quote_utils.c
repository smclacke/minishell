/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_quote_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/28 16:34:53 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/14 16:42:22 by smclacke      ########   odam.nl         */
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
 * 
 * it now at least doesnt only increment i and j... hawhaw
*/
void	copy_and_increment(char *new_str, char *str, int *i, int *j)
{
	new_str[(*j)] = str[(*i)];
	(*i)++;
	(*j)++;
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
