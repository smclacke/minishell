/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/11/07 18:59:17 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param lst  parser linked list
 * @brief checks if there's an space in the next node.
*/
static int	space_check(t_parser *lst)
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
static void	export_print(t_env *env)
{
	while (env != NULL)
	{
		if (env->has_value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

/**
 * @param str string from the t_parser node containing export argument
 * @brief checks string if there's an equal sign present
*/
static char	*check_for_equal_sign(char *str)
{
	char	*comp_str;

	comp_str = NULL;
	if (str[ft_strlen(str) - 1] == '=')
		comp_str = ft_substr(str, 0, (ft_strlen(str) - 1));
	return (comp_str);
}

/**
 * @param e double pointer to environmet list
 * @param node pointer to node in list given in the form of a string
 * @param n_k string to contain new key value
 * @param n_v string to contain new value value
 * @brief reassigns lines in the environment when export arguments is
 * 		  is an already excisting key.
*/
static bool	reassign_env(t_env **e, t_parser *node, char *n_k, char *n_v)
{
	t_env	*head;
	int		has_value;
	char	*str;
	char	*comp_str;

	head = *e;
	str = node->str;
	comp_str = check_for_equal_sign(str);
	while (head)
	{
		if (mini_strcmp(comp_str, head->key) == 0)
		{
			printf("\n\nhi\n\n");
			if (str[ft_strlen(str) == '='])
			{
				head->full = node->str;
				has_value = get_key_value(node->str, &n_k, &n_v);
				head->value = n_v;
				head->key = n_k;
				return (true);
			}
		}
		head = head->next;
	}
	return (false);
}

/**
 * @param node pointer to node in list given in the form of a string
 * @param env pointer to linked list
 * @brief export with no options
 * @todo I think i dont proper set the full part of my environment in here
 * check make env.
*/
void	ft_export(t_parser *node, t_env **env)
{
	char	*new_key;
	char	*new_value;
	int		h_v;
	// char	*full_str;
	t_env	*new_node;

	new_key = NULL;
	new_value = NULL;
	// full_str = node->str;
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
	h_v = get_key_value(node->str, &new_key, &new_value);
	// (*env)->full = get_full(full_str);
	new_node = env_lstnew(new_key, new_value, node->str, h_v);
	env_lstadd_back(env, new_node);
}
