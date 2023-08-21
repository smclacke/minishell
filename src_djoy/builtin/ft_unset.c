/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 17:53:37 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/21 22:14:03 by dreijans      ########   odam.nl         */
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
		// }
		// break ;
		// if (node->next != NULL)
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
		printf("everything ok?\n");
		printf("str = [%s]\n", str);
		if (!strncmp(current->key, str, strlen(str)))
		{
			printf("hello there\n");
			if (previous != NULL)
				previous->next = current->next;
			else
			{
				*env = current->next;
			}
			tmp = current;
			current = current->next;
			free(tmp);
			printf("okay now\n");
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}

// if (!strncmp(current->key, node->next->str[i], strlen(node->next->str[i])))