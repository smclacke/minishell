/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_is_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 19:21:07 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/24 13:24:09 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @brief	specifically for checking the values after dollar sign
 * 			need to check if expandable if not another dollar, quote or space
*/
int	expandable_str(int c)
{
	if (!is_dollar_or_quote(c) && !ft_isspace(c))
		return (1);
	return (0);
}

int	is_dollar_or_quote(int c)
{
	return (ft_dollar(c) || ft_isquote(c));
}
