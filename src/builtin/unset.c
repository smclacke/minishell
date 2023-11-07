/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:51 by dreijans      #+#    #+#                 */
/*   Updated: 2023/11/07 18:19:30 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param str key given as string
 * @param env pointer to environment
 * @brief loops through list and finds the key's to delete
*/
static void	mini_remove_env(char *str, t_env **env)
{
	t_env	*previous;
	t_env	*current;
	t_env	*tmp;

	previous = NULL;
	current = *env;
	tmp = NULL;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, str, ft_strlen(str)))
		{
			if (previous != NULL)
			{
				previous->next = current->next;
				printf("prev = [%s]\n", previous->key);
				// printf("prev->next = [%s]\n", previous->next->key);
				// printf("curr->next = [%s]\n", current->next->key);
				// printf("curr = [%s]\n", current->key);
			}
			else
			{
				*env = current->next;
				// printf("env = [%p]\n", *env);
			}
			tmp = current;
			free_all(tmp);
			current = current->next;
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}

/**
 * @param argv terminal given arguments (for now)
 * @param env pointer to environment
 * @brief unset values by deleting nodes in env linked list
*/
void	ft_unset(t_parser *node, t_env **env)
{
	if (word_check(node) == 1)
		return ;
	if (node != NULL)
		node = node->next;
	while (node)
	{
		mini_remove_env(node->str, env);
		node = node->next;
	}
}
