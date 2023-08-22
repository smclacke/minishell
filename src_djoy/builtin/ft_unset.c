/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 17:53:37 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/22 18:20:20 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

void	feree(t_env *env)
{
	free(env->value);
	free(env->key);
	free(env->full);
	free(env);
}

/**
 * @param argv terminal given arguments (for now)
 * @param env pointer to environment
 * @brief unset values by deleting nodes in env linked list
*/
void	ft_unset(t_parser *node, t_env **env)
{
	if (node != NULL)
		node = node->next;
	while (node)
	{
		mini_remove_env(node->str, env);
		node = node->next;
	}
}

void	mini_remove_env(char *str, t_env **env)
{
	t_env	*previous;
	t_env	*current;
	t_env	*tmp;

	previous = NULL;
	current = *env;
	tmp = NULL;
	while (current != NULL) 
	{
		if (!ft_strncmp(current->key, str, strlen(str)))
		{
			if (previous != NULL)
				previous->next = current->next;
			else 
				*env = current->next;
			tmp = current;
			current = current->next;
			feree(tmp);
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}
