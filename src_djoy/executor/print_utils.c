/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 14:49:26 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/31 19:22:57 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key or value
*/
void	print_list(t_env *env)
{
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key or value
*/
void	print_list_key(t_env *env)
{
	while (env != NULL)
	{
		printf("%s\n", env->key);
		env = env->next;
	}
}

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key or value
*/
void	print_list_value(t_env *env)
{
	while (env != NULL)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
}
