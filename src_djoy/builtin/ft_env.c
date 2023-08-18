/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 18:12:37 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/18 17:40:23 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key and value
 * @todo doesnt give update version after cd etc need to do that??
 * whyyyyyy??????
 * why overschrijven hoeezooo???
*/
void	ft_env(t_env *env)
{
	// printf("what the shell env\n");
	// while (env != NULL)
	// {
		// printf("%s=%s\n", env->key, env->value);
		// env = env->next;
	// }
	// print_list(env);
	print_list_full(env);
}
