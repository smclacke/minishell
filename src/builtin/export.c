/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/11/28 22:06:38 by dreijans      ########   odam.nl         */
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
		else
			printf("declare -x %s\n", env->key);
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
	int		i;

	comp_str = NULL;
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	comp_str = ft_substr(str, 0, i);
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
	char	*comp_str;
	char	*temp_full;
	char	*temp_value;
	char	*temp_key;

	head = *e;
	comp_str = check_for_equal_sign(node->str);
	while (head)
	{
		if (mini_strcmp(comp_str, head->key) == 0)
		{
			if (node->str[ft_strlen(node->str) == '='])
			{
				temp_full = head->full;
				head->full = comp_str;
				free(temp_full);
				has_value = get_key_value(node->str, &n_k, &n_v);
				temp_value = head->value;
				head->value = n_v;
				free(temp_value);
				temp_key = head->key;
				head->key = n_k;
				free(temp_key);
				return (true);
			}
		}
		head = head->next;
	}
	free(comp_str);
	return (false);
}

/**
 * @param node pointer to node in list given in the form of a string
 * @param env pointer to linked list
 * @brief export with no options
 * @todo free things i think and norm proof also double free 
 * with freeing in an unrelated spot 
 * might be overwriting a pointer and not allocating a new string yey.
 * NORM DEZE HELE PAGE
 * 
*/
void	ft_export(t_parser *node, t_env **env)
{
	char	*new_key;
	char	*new_value;
	int		h_v;
	t_env	*new_node;
	char	*new_full;

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
	h_v = get_key_value(node->str, &new_key, &new_value);
	new_full = ft_strdup(node->str);
	if (new_full == NULL)
		return ;//really?? error message 
	new_node = env_lstnew(new_key, new_value, new_full, h_v);
	env_lstadd_back(env, new_node);
}