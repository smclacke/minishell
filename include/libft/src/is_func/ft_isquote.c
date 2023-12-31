/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isquote.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 13:22:48 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/02 20:43:08 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_isquote(int c)
{
	return (c == '\'' || c == '\"');
}
