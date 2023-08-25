/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 17:53:37 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/25 15:48:18 by dreijans      ########   odam.nl         */
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

// !! if same keyname overwrite that with new else add

// bash: export: `9h=haha': not a valid identifier
// bash-3.2$ unset 999
// bash-3.2$ export djoyke =gek
// bash: export: `=gek': not a valid identifier
// bash-3.2$ export djoyke=gek gggg (working)
// bash-3.2$ env (working)
// djoyke=gek (working)
// bash-3.2$ export djoyke="gek gggg" (two words if it's in quotations)
// bash-3.2$ env
// env part:
// djoyke=gek gggg
// bash-3.2$
// bash-3.2$ export djoyke= gek (working)
// bash-3.2$ env (working)
// djoyke= (working)

/* make function for unset and export checking if 
key (word) has:
	 capital (H), lowercase (h), underscore (_) as first letter 
else give error if given 99= as key
	 bash: export: `99=': not a valid identifier
	 rest of word can only have numbers, letters and underscore.
else give error export d@@=haha
	bash: export: `d@@=haha': not a valid identifier
same for unset */
