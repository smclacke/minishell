/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils_two.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:27:49 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/09 19:33:13 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param temp temporary placeholder
 * @param str old working directory string
 * @param env environment in linked list
 * @brief replaces the value of set key in the environment
*/
void	reasing_value(char *temp, char *str, t_env *env)
{
	temp = env->value;
	env->value = str;
	free(temp);
}
