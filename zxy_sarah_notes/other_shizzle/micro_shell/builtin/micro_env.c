/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 18:12:37 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/27 15:29:23 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key and value
*/
void	micro_env(t_env *env)
{
	printf("what the shell env\n");
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
