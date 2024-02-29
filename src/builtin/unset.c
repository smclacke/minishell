/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:51 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/29 21:43:52 by dreijans      ########   odam.nl         */
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
		if (ft_strncmp(current->key, str, ft_strlen(str) + 1) == 0)
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

/**
 * @param node parser linked list
 * @param env pointer to environment
 * @brief unset values by deleting nodes in env linked list
 * @note if path is unset cant do env in bash
*/
void	ft_unset(t_parser *node, t_env **env)
{
	int	i;

	i = 0;
	if (node->proc->str_count == 0)
		return ;
	while (i < node->proc->str_count)
	{
		mini_remove_env(node->proc->str[i], env);
		i++;
	}
}
