/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 14:42:33 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/21 18:38:25 by dreijans      ########   odam.nl         */
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
void	ft_export(t_parser *node, t_env *env)
{
	char	*new_key;
	char	*new_value;
	t_env	*new_node;

	new_key = NULL;
	new_value = NULL;
	node = node->next; //for now until parser parses cmd with string in one node
	if (ft_strchr(node->str, '=') == 0)
		mini_error("strchr", errno);
	reassign_env(env, node, new_key, new_value);
	get_key_value(node->str, &new_key, &new_value);
	new_node = env_lstnew(new_key, new_value, node->str);
	env_lstadd_back(&env, new_node);
}

void	reassign_env(t_env *env, t_parser *node, char *n_k, char *n_v)
{
	while (env)
	{
		if (mini_strcmp(node->str, env->full) == 0)
		{
			env->full = node->str;
			get_key_value(node->str, &n_k, &n_v);
			env->value = n_v;
			env->key = n_k;
			return ;
		}
		env = env->next;
	}
}
