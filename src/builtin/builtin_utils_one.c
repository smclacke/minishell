/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils_one.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 15:47:58 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/06 21:47:03 by dreijans      ########   odam.nl         */
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
 * @todo exit codes
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
	else if (cmd_type == ECHO)
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
 * @return 1 if not alphanumeric, 0 is alphanumeric
*/
static bool	is_valid_key(t_parser *temp, char *key, char *cmd)
{
	int	i;
	printf("key = %s\n", key);

	if ((ft_isalpha(key[0]) == 0) && key[0] != '_')
	{
		put_custom_error(temp, cmd);
		return false;
	}
	i = 1;
	while (key[i])
	{
		if (key[i] != '_' && ft_isalnum(key[i]) == 0)
		{
			put_custom_error(temp, cmd);
			return false;
		}
		i++;
	}
	return true;
}

/**
 * @param lst linked list
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
 * @todo the !word error part is for this edge case :
 * export "" test=a
 * 
 * but comprimises this edge case which didnt work before
 * but now doesnt work in a different way:
 * export var=a
 * export $var=test
 * echo $var $a
 * @todo why do I need list and value and what do my errors do?
 * better way to do this
 * 	words = null_check(str, lst);
	if (!words)
	{
		put_custom_error(lst, "export");
		mini_error(E_GENERAL, lst);
		return (true);
	}
	if ((mini_strcmp(cmd, "unset") == 0) && words[1])
	{
		put_custom_error(temp, cmd);
		return (true);
	}
	if (key_value_check(lst, words, "export") == 1)
	{
		ft_free_arr(words);
		return (true);
	}
*/
bool	word_check(t_parser *lst, char *key, char *value)
{
	t_parser	*temp;
	char		*cmd;

	cmd = lst->proc->cmd;
	temp = lst;
	if ((mini_strcmp(cmd, "unset") == 0) && value)
	{
		put_custom_error(temp, cmd);
		return (true);
	}
	if (is_valid_key(lst, key, "export") == false)
	{
		free(key);
		free(value);
		return (true);
	}
	return (false);
}

/**
 * @param lst single pointer to environmet list
 * @param str string passed from parser
 * @param value string to contain new value value
 * @brief reassigns lines in the environment
 * @todo changed to char *str in this function
*/
void	replace_node(t_env *lst, char *str, char *value)
{
	char	*temp;

	temp = lst->full;
	lst->full = str;
	free(temp);
	temp = lst->value;
	lst->value = value;
	free(temp);
}
