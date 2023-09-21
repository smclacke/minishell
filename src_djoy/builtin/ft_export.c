/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 14:42:33 by dreijans      #+#    #+#                 */
/*   Updated: 2023/09/21 18:16:04 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

int	space_check(t_parser *lst)
{
	t_parser	*temp;

	temp = lst->next;
	if (temp->next)
	{
		temp = temp->next;
		put_custom_error(temp, "export");
		return (1);
	}
	return (0);
}

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key or value
 * with declare in front
*/
void	export_print(t_env *env)
{
	while (env != NULL)
	{
		printf("declare -x %s=%s\n", env->key, env->value);
		env = env->next;
	}
}

/**
 * @param node pointer to node in list given in the form of a string
 * @param env pointer to linked list
 * @brief export with no options
 * @todo first character cannot have a number but everything else can have
 * check export edge cases
 * WHY (*env)????
*/
void	ft_export(t_parser *node, t_env **env)
{
	char	*new_key;
	char	*new_value;
	t_env	*new_node;

	new_key = NULL;
	new_value = NULL;
	if (!node->next)
	{
		export_print(*env);
		return ;
	}
	if (space_check(node) == 1)
		return ;
	if (word_check(node) == 1)
		return ;
	node = node->next;
	if (ft_strchr(node->data_type->strs, '=') == 0)
		mini_error("strchr", errno);
	if (reassign_env(env, node, new_key, new_value) == 1)
		return ;
	get_key_value(node->data_type->strs, &new_key, &new_value);
	new_node = env_lstnew(new_key, new_value, node->data_type->strs);
	env_lstadd_back(env, new_node);
}

bool	reassign_env(t_env **env, t_parser *node, char *n_k, char *n_v)
{
	t_env	*head;

	head = *env;
	while (head)
	{
		if (mini_strcmp(node->data_type->strs, head->full) == 0)
		{
			head->full = node->data_type->strs;
			get_key_value(node->data_type->strs, &n_k, &n_v);
			head->value = n_v;
			head->key = n_k;
			return (true);
		}
		head = head->next;
	}
	return (false);
}

//content needs to be freed
