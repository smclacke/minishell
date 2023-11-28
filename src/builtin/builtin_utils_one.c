/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils_one.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 15:47:58 by dreijans      #+#    #+#                 */
/*   Updated: 2023/11/28 21:47:45 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"
// #include <limits.h>

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
void	do_builtin(t_parser *node, t_env **env)
{
	if (!node->cmd)
		mini_error("parser", errno);
	else if (mini_strcmp(node->cmd, "echo") == 0)
		ft_echo(node);
	else if (mini_strcmp(node->cmd, "cd") == 0)
		ft_cd(node, env);
	else if (mini_strcmp(node->cmd, "pwd") == 0)
		ft_pwd();
	else if (mini_strcmp(node->cmd, "export") == 0)
		ft_export(node, env);
	else if (mini_strcmp(node->cmd, "unset") == 0)
		ft_unset(node, env);
	else if (mini_strcmp(node->cmd, "env") == 0)
		ft_env(*env);
	else if (mini_strcmp(node->cmd, "exit") == 0)
		ft_exit(node);
}

/**
 * @param temp linked list
 * @param words 2D array with seperate words key and value
 * @param cmd string containing command
 * @brief checks if key and value are alphanumeric
 * @return 1 if not alphanumeric, 0 is alphanumeric
*/
int	key_value_check(t_parser *temp, char **words, char *cmd)
{
	int	i;

	if ((ft_isalpha(words[0][0]) == 0) && words[0][0] != '_')
	{
		put_custom_error(temp, cmd);
		return (1);
	}
	i = 1;
	while (words[0][i])
	{
		if (words[0][i] != '_' && ft_isalnum(words[0][i]) == 0)
		{
			put_custom_error(temp, cmd);
			return (1);
		}
		i++;
	}
	return (0);
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
 * @return true if nothing wrong found with the words
*/
bool	word_check(t_parser *lst)
{
	t_parser	*temp;
	char		**words;
	char		*cmd;

	cmd = lst->cmd;
	temp = lst->next;
	words = NULL;
	words = ft_split(temp->str, '=');
	if ((mini_strcmp(cmd, "unset") == 0) && words[1])
	{
		put_custom_error(temp, cmd);
		return (true);
	}
	if (words == NULL)
		mini_error("malloc split", errno);
	if (key_value_check(temp, words, cmd) == 1)
	{
		ft_free_arr(words);
		return (true);
	}
	ft_free_arr(words);
	return (false);
}
