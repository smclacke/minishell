/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 17:53:37 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/19 21:21:04 by djoyke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param argv terminal given arguments (for now)
 * @param env pointer to environment
 * @brief unset values by deleting nodes in env linked list
*/
void	ft_unset(t_parser *node, t_env *env)
{
	t_env	*temp;

	temp = NULL;
	while (env->next != NULL)
	{
		if (ft_strcmp(env->next->key, &node->str[0]) == 0)
		{
			temp = env->next;
			env->next = env->next->next;
			free(temp);
		}
		env = env->next;
	}
	print_list(env);
}
