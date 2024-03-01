/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:21 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/01 21:38:42 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key or value
 * with declare in front
 *  do I need to print this on the STDERR_FILENO?
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
 * @param env double pointer to environmet list
 * @param var export struct
 * @brief reassigns lines in the environment when export arguments is
 * 		  is an already excisting key.
*/
static bool	reassign_env(t_env **env, t_export var)
{
	t_env	*lst;

	lst = *env;
	while (lst)
	{
		if (mini_strcmp(var.key, lst->key) == 0)
		{
			replace_node(lst, var);
			return (true);
		}
		lst = lst->next;
	}
	return (false);
}

/**
 * @param node pointer to node in list given in the form of a string
 * @param ex_var export struct
 * @param i iterator
 * @brief checks if key and value are valid strings
 * @return true if valid false if invalid
*/
static bool	key_value_check(t_parser *node, t_export var, int i)
{
	if (word_check(node, var.key) == true)
	{
		if (i < node->proc->str_count)
		{
			free(var.key);
			free(var.value);
			free(var.str);
			return (false);
		}
	}
	return (true);
}

static bool	str_count_check(t_parser *node, t_env **env)
{
	if (node->proc->str_count == 0)
	{
		export_print(*env);
		return (false);
	}
	return (true);
}

/**
 * @param node pointer to node in list given in the form of a string
 * @param env pointer to linked list
 * @brief export with no options, 
 * @note double free with freeing in an unrelated spot 
 * might be overwriting a pointer and not allocating a new string.
 * When no arguments are given, the results are unspecified. man export!!
*/
void	ft_export(t_parser *node, t_env **env)
{
	int			i;
	int			j;
	t_export	var;

	i = 0;
	j = 0;
	if (str_count_check(node, env) == false)
		return ;
	while (i < node->proc->str_count)
	{
		j = 0;
		var.str = mini_strdup(node->proc->str[i]);
		while (var.str[j] && var.str[j] != '=')
			j++;
		var.has_value = get_key_value(var.str, &var.key, &var.value);
		if (key_value_check(node, var, i) == false)
		{
			i++;
			continue ;
		}
		if (reassign_env(env, var) == true)
			return ;
		make_node(env, var);
		i++;
	}
}
