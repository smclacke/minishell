/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 17:53:37 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/22 16:26:49 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param argv terminal given arguments (for now)
 * @param env pointer to environment
 * @brief unset values by deleting nodes in env linked list
*/
void	ft_unset(t_parser *node, t_env **env)
{
	while (node)
	{
		printf("are we there?\n");
		mini_remove_env(node->next->str, env);
		if (node->next != NULL)
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
		printf("str = [%s]\n", str);
		if (!ft_strncmp(current->key, str, strlen(str)))
		{
			previous->next = current;
			current = current->next;
			printf("hello there\n");
		}
		if (ft_strncmp(current->key, str, strlen(str)))
		{
			previous->next = current;
			tmp = current;
			current = current->next;
			free(tmp);
		}
		current = current->next;
	}
}
