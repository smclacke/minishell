/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_spaced.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 19:44:26 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/16 19:54:32 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_spaced(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || ft_dollar(str[i])
			|| ft_isquote(str[i]))
			return (1);
		i++;
	}
	return (0);
}
