/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_arr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 20:53:30 by smclacke      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/10/17 19:21:07 by dreijans      ########   odam.nl         */
=======
/*   Updated: 2023/10/17 19:43:19 by smclacke      ########   odam.nl         */
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
