/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils_two.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:27:49 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/26 14:09:24 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param temp temporary placeholder
 * @param str old working directory string
 * @param env environment in linked list
 * @brief replaces the value of set key in the environment
*/
void	reassign_values(char *cwd, t_env *node, t_parser *head)
{
	char	*key_equal;
	char	*new_full;

	(void)head;
	free(node->value);
	node->value = mini_strdup(cwd);
	key_equal = mini_strjoin(node->key, "=");
	new_full = mini_strjoin(key_equal, cwd);
	free(key_equal);
	free(node->full);
	node->full = new_full;
}

/**
 * @param env environment in linked list
 * @param str string to compare to key value env
 * @brief finds key value of env in the env list
 * @return returns NULL if nothing found,
 * returns value if key is found
*/
char	*ft_getenv(t_env *env, char *str)
{
	while (env)
	{
		if (mini_strcmp(str, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/**
 * @param lst parser linked list
 * @brief checks if arguments are more than one
 * throws error message if true.
*/
bool	too_many_args(t_parser *lst)
{
	if (lst->proc->str_count > 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(lst->proc->cmd, STDERR_FILENO);
		ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
		lst->exit_code = E_GENERAL;
		return (true);
	}
	return (false);
}

/**
 * @param env environment linked list
 * @param ex_var export struct
 * @brief makes all components for new node and adds to env linked list
*/
void	make_node(t_env **env, t_export var)
{
	t_env	*new_node;

	new_node = env_lstnew(var.key, var.value, var.str, var.has_value);
	if (!new_node)
	{
		free_env(env);
		free(new_node);
		return ;
	}
	env_lstadd_back(env, new_node);
}
