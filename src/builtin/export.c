/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:21 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/06 18:24:41 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

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
//  * @param node pointer to node in list given in the form of a string
 * @param str string passed by parser
 * @param n_k string to contain new key value
 * @param n_v string to contain new value value
 * @brief reassigns lines in the environment when export arguments is
 * 		  is an already excisting key.
*/
static bool	reassign_env(t_env **e, char *str, char *n_k, char *n_v)
{
	t_env	*head;
	char	*comp_str;
	char	*temp;

	head = *e;
	comp_str = check_for_equal_sign(str);
	while (head)
	{
		if (mini_strcmp(comp_str, head->key) == 0)
		{
			if (str[ft_strlen(str) == '='])
			{
				temp = head->full;
				head->full = comp_str;
				free(temp);
				replace_str(head, str, n_k, n_v);
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
 * @brief export with no options, learned that double free 
 * with freeing in an unrelated spot 
 * might be overwriting a pointer and not allocating a new string.
 * @todo 
 * env does show the expanded version.
 * check if multiple ===== what do you do?
 * 
*/
void	ft_export(t_parser *node, t_env **env)
{
	char	*new_key;
	char	*new_value;
	int		i;

	new_key = NULL;
	new_value = NULL;
	i = 0;
	if (node->proc->str_count == 0)
	{
		export_print(*env);
		return ;
	}
	while (i < node->proc->str_count)
	{
		if (word_check(node->proc->str[i], node) == 1)
			return ;
		if (reassign_env(env, node->proc->str[i], new_key, new_value) == 1)
			return ;
		make_node(node->proc->str[i], env, new_key, new_value);
		node->exit_code = E_USAGE;
		i++;
	}
}
