/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SarahLouise <SarahLouise@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 18:17:46 by SarahLouise   #+#    #+#                 */
/*   Updated: 2023/07/02 18:21:46 by SarahLouise   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// int	main()
// {
// 	char	src[] = "World";
// 	char	dest[] = "Hello";

// 	printf("src: %s, dest: %s\n", src, dest);
// 	ft_strcpy(dest, src);
// 	printf("src: %s, dest: %s\n", src, dest);
// }
