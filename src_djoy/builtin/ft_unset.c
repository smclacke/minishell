/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 17:53:37 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/25 14:40:29 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param env pointer to environment
 * @brief free's content plus node.
*/
void	free_all(t_env *env)
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

/**
 * @param str key given as string
 * @param env pointer to environment
 * @brief loops through list and finds the key's to delete
*/
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
			free_all(tmp);
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}
