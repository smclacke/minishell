/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_unset.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 17:53:37 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/27 16:47:47 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param argv terminal given arguments (for now)
 * @param env pointer to environment
 * @brief unset values by deleting nodes in env linked list
*/
// void	micro_unset(t_parser *node, t_env *env)
// {
// 	t_env	*temp;

// 	temp = NULL;
// 	while (env->next != NULL)
// 	{
// 		if (ft_strcmp(env->next->key, node->str[0]) == 0)
// 		{
// 			temp = env->next;
// 			env->next = env->next->next;
// 			free(temp);
// 		}
// 		env = env->next;
// 	}
// 	micro_print_list(env);
// }
