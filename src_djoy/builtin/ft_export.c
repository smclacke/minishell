/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 14:42:33 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/30 18:10:12 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param node pointer to node in list given in the form of a string
 * @param env pointer to linked list
 * @brief export with no options
 * @todo first character cannot have a number but everything else can have
 * check export edge cases
 * remove line 33: when parsing is fixed
*/
void	ft_export(t_parser *node, t_env **env)
{
	char	*new_key;
	char	*new_value;
	t_env	*new_node;

	new_key = NULL;
	new_value = NULL;
	if (word_check(node) == 0)
		return ;
	node = node->next; //for now until parser parses cmd with string in one node
	if (ft_strchr(node->str, '=') == 0)
		mini_error("strchr", errno);
	if (reassign_env(env, node, new_key, new_value) == 1)
		return ;
	get_key_value(node->str, &new_key, &new_value);
	new_node = env_lstnew(new_key, new_value, node->str);
	env_lstadd_back(env, new_node);
}

bool	reassign_env(t_env **env, t_parser *node, char *n_k, char *n_v)
{
	t_env	*head;

	head = *env;
	while (head)
	{
		if (mini_strcmp(node->str, head->full) == 0)
		{
			head->full = node->str;
			get_key_value(node->str, &n_k, &n_v);
			head->value = n_v;
			head->key = n_k;
			return (true);
		}
		head = head->next;
	}
	return (false);
}

//unset everything and make sure the first nod is freed as well
//content needs to be freed
