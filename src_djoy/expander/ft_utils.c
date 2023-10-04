/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 12:18:59 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/04 13:39:22 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**

 * @param data expand struct
 * @brief initializes struct
*/
void	init_expand_struct(t_expand *data)
{
	data->before_dollar = NULL;
	data->env_value = NULL;
	data->comp_str = NULL;
}

/**
 * @param exp expand struct
 * @brief frees parts of the struct and entire struct
*/
void	free_remain_struct(t_expand *data)
{
	if (data->before_dollar != NULL)
		free (data->before_dollar);
	if (data->env_value != NULL)
		free (data->env_value);
	if (data->comp_str != NULL)
		free (data->comp_str);
	if (data != NULL)
		free (data);
}
