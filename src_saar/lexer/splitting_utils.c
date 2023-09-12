/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:45:59 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/12 17:53:27 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

char	*which_quote(char c)
{
	if (c == '\"')
		return (DOUBLE_Q);
	else if (c == '\'')
		return (SINGLE_Q);
	return (NULL);
}
