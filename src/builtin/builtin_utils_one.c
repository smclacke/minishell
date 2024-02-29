/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils_one.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 15:47:58 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/29 21:22:09 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param env pointer to environment
 * @brief free's content plus node.
*/
void	free_all(t_env *env)
{
	free(env->value);
	free(env->key);
	free(env->full);
	free(env);
}

/**
 * @param node node in linked list
 * @param env string or char to compare with
 * @brief checks arguments to find built-ins:
 * echo, cd, pwd, export, unset, env and exit
*/
void	do_builtin(t_parser *node, t_env **env, int cmd_type)
{
	if (cmd_type == EXIT)
		ft_exit(node);
	else if (cmd_type == CD)
		ft_cd(node, env);
	else if (cmd_type == EXPORT)
		ft_export(node, env);
	else if (cmd_type == UNSET)
		ft_unset(node, env);
	else if (cmd_type == 5)
		ft_echo(node, env);
	else if (cmd_type == PWD)
		ft_pwd(node);
	else if (cmd_type == ENV)
		ft_env(*env, node);
}

/**
 * @param temp linked list
 * @param words 2D array with seperate words key and value
 * @param cmd string containing command
 * @brief checks if key and value are alphanumeric
 * @return true if not alphanumeric, false is alphanumeric
*/
static bool	is_valid_key(t_parser *temp, char *key, char *cmd)
{
	int	i;

	if ((ft_isalpha(key[0]) == 0) && key[0] != '_')
	{
		put_custom_error(temp, key, cmd);
		return (false);
	}
	i = 1;
	while (key[i])
	{
		if (key[i] != '_' && ft_isalnum(key[i]) == 0)
		{
			put_custom_error(temp, key, cmd);
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @param lst linked list
 * @param key string containing key
 * @param value string containing value
 * @brief checks if the words are export and unset norm
 * proof.
 * key (word) first letter has:
 * capital (H), lowercase (h), underscore (_) as first letter 
 * else give error if given 99=djoyke as key
 * minishell: export: `99=djoyke': not a valid identifier
 * rest of word can only have numbers, letters and underscore.
 * else give error export d@@=haha
 * minishell: export: `d@@=haha': not a valid identifier
 * same for unset
 * @return true if wrong found with the words
*/
bool	word_check(t_parser *lst, char *key)
{
	if (is_valid_key(lst, key, "export") == false)
		return (true);
	return (false);
}

/**
 * @param lst single pointer to environmet list
 * @param str string passed from parser
 * @param value string to contain new value value
 * @brief reassigns lines in the environment
*/
void	replace_node(t_env *lst, t_export var)
{
	char	*temp;

	temp = lst->full;
	lst->full = var.str;
	free(temp);
	temp = lst->key;
	lst->key = var.key;
	free(temp);
	temp = lst->value;
	lst->value = var.value;
	var.has_value = TRUE;
	lst->has_value = var.has_value;
	free(temp);
}
