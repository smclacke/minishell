/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 12:18:59 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/04 12:19:02 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

void	init_expand_struct(t_expand *data)
{
	data->before_dollar = NULL;
	data->env_value = NULL;
	data->comp_str = NULL;
}

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
