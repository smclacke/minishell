/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 14:42:33 by dreijans      #+#    #+#                 */
/*   Updated: 2023/09/21 20:26:21 by dreijans      ########   odam.nl         */
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
		if (env->has_value)
			printf("declare -x %s=%s\n", env->key, env->value);
		env = env->next;
	}
}

char	*check_for_equal_sign(char *str)
{
	char	*comp_str;

	comp_str = NULL;
	if (str[ft_strlen(str) - 1] == '=')
		comp_str = ft_substr(str, 0, (ft_strlen(str) - 1));
	return (comp_str);
}

/**
 * @param node pointer to node in list given in the form of a string
 * @param env pointer to linked list
 * @brief export with no options
*/
void	ft_export(t_parser *node, t_env **env)
{
	char	*new_key;
	char	*new_value;
	int		h_v;
	t_env	*new_node;

	new_key = NULL;
	new_value = NULL;
	h_v = 0;
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
	if (reassign_env(env, node, new_key, new_value) == 1)
		return ;
	h_v = get_key_value(node->data_type->strs, &new_key, &new_value);
	new_node = env_lstnew(new_key, new_value, node->data_type->strs, h_v);
	env_lstadd_back(env, new_node);
}

bool	reassign_env(t_env **e, t_parser *node, char *n_k, char *n_v)
{
	t_env	*head;
	int		has_value;
	char	*str;
	char	*comp_str;

	head = *e;
	str = node->data_type->strs;
	comp_str = check_for_equal_sign(str);
	while (head)
	{
		if (mini_strcmp(comp_str, head->key) == 0)
		{
			if (str[ft_strlen(str) == '='])
			{
				head->full = node->data_type->strs;
				has_value = get_key_value(node->data_type->strs, &n_k, &n_v);
				head->value = n_v;
				head->key = n_k;
				return (true);
			}
		}
		head = head->next;
	}
	return (false);
}
