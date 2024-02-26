/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SarahLouise <SarahLouise@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 17:02:40 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/23 21:17:11 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}
