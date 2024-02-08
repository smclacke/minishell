/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:21 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/08 20:52:59 by dreijans      ########   odam.nl         */
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
		printf("has_value = %i\n", env->has_value);
		if (env->has_value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

/**
 * @param env double pointer to environmet list
 * @param ex_var export struct
 * @brief reassigns lines in the environment when export arguments is
 * 		  is an already excisting key.
 * @todo leak check and norm it
*/
static bool	reassign_env(t_env **env, t_export ex_var)
{
	t_env	*lst;

	lst = *env;
	while (lst)
	{
		if (mini_strcmp(ex_var.key, lst->key) == 0)
		{
			// free(key);
			replace_node(lst, ex_var);
			return (true);
		}
		lst = lst->next;
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
 * Norm it!
*/
void	ft_export(t_parser *node, t_env **env)
{
	int		i;
	int		j;
	t_export ex_var;

	i = 0;
	j = 0;
	if (node->proc->str_count == 0)
	{
		export_print(*env);
		return ;
	}
	while (i < node->proc->str_count)
	{
		ex_var.str = node->proc->str[i];
		while (ex_var.str[j] && ex_var.str[j] != '=')
			j++;
		ex_var.has_value = get_key_value(ex_var.str, &ex_var.key, &ex_var.value);
		if (word_check(node, ex_var.key, ex_var.value) == true && i == (node->proc->str_count - 1))
		{
			free(ex_var.key);
			free(ex_var.value);
			return ;
		}
		if (reassign_env(env, ex_var) == true && i == (node->proc->str_count - 1))
			return ;
		make_node(env, ex_var);
		node->exit_code = E_USAGE;
		i++;
	}
}
