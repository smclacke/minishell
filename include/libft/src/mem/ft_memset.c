/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SarahLouise <SarahLouise@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 11:27:22 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/02 15:04:36 by SarahLouise   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/**
 * @brief
 * writes len bytes of value c (converted to an unsigned char)
 * to the string b. 
 * c is set as an int but the function fills 
 * the block of memory using the 
 * unsigned char converstion of this value.
 * 
 * 
 * @param b void pointer to the block of memory to fill 
 * @param c int value to be set
 * @param len size_t number of bytes to be set to the value
 * @return its first argument
*/
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = ((unsigned char *)b);
	while (len-- > 0)
		*(ptr++) = ((unsigned char)c);
	return (b);
}
