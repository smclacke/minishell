/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:21 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/06 21:40:06 by dreijans      ########   odam.nl         */
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
 * @param e double pointer to environmet list
//  * @param node pointer to node in list given in the form of a string
 * @param str string passed by parser
 * @param n_k string to contain new key value
 * @param n_v string to contain new value value
 * @brief reassigns lines in the environment when export arguments is
 * 		  is an already excisting key.
*/
static bool	reassign_env(t_env **e, char *str, char *key, char *value)
{
	t_env	*head;

	head = *e;
	while (head)
	{
		if (mini_strcmp(key, head->key) == 0)
		{
			free(key);
			replace_node(head, str, value);
			return (true);
		}
		head = head->next;
	}
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
	int		i;

	i = 0;
	if (node->proc->str_count == 0)
	{
		export_print(*env);
		return ;
	}
	while (i < node->proc->str_count)
	{
		char *str = node->proc->str[i];

		while (str[i] && str[i] != '=')
		{
			i++;
		}
		
		char *key = ft_substr(str, 0, i);
		char *value = ft_substr(str, i + 1, ft_strlen(str + i) + 1);

		if (word_check(node, key, value) == true)
			return ;
		if (reassign_env(env, str, key, value) == true)
			return ;

		make_node(str, env, key, value);
		node->exit_code = E_USAGE;
		i++;
	}
}
