/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:45:59 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/12 18:35:08 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

bool	is_quote(char input)
{
	if (input == '\'' || input == '\"')
		return(true);
	return (false);
}

bool	is_meta(char *input)
{
	if (ft_strcmp(input, MOREMORE) == 0)
		return (true);
	else if (ft_strcmp(input, LESSLESS) == 0)
		return (true);
	else if (ft_strcmp(input, MORE) == 0)
		return (true);
	else if (ft_strcmp(input, LESS) == 0)
		return (true);
	else if (ft_strcmp(input, PIPE) == 0)
		return (true);
	return (false);
}
