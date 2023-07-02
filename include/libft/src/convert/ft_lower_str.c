/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lower_str.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: SarahLouise <SarahLouise@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 22:17:06 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/02 15:03:53 by SarahLouise   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_lower_str(char *str)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}
