/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_issquote.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 20:36:05 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/02 20:36:14 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_issquote(int c)
{
	return (c == '\'');
}