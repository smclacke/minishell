/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_arr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 20:53:30 by smclacke      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/10/16 18:00:39 by dreijans      ########   odam.nl         */
=======
/*   Updated: 2023/10/13 22:17:53 by smclacke      ########   odam.nl         */
>>>>>>> sarah
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
