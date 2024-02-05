/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils_two.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:27:49 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/05 19:19:24 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param temp temporary placeholder
 * @param str old working directory string
 * @param env environment in linked list
 * @brief replaces the value of set key in the environment
 * @todo exit codes
*/
void	reassign_values(char *cwd, t_env *node, t_parser *head)
{
	char	*key_equal;
	char	*new_full;

	free(node->value);
	node->value = ft_strdup(cwd);
	if (!node->value)
		mini_error(E_GENERAL, head);
	key_equal = ft_strjoin(node->key, "=");
	if (!key_equal)
		mini_error(E_GENERAL, head);
	new_full = ft_strjoin(key_equal, cwd);
	if (!key_equal)
		mini_error(E_GENERAL, head);
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
 * @brief returns list size
*/
int	list_iter(t_parser *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
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
		dprintf(STDERR_FILENO, ARG_ERROR, lst->proc->cmd);
		return (true);
	}
	return (false);
}

/**
 * @param node node from parser linked list
 * @param env environment linked list
 * @param new_k char str containing new key
 * @param new_v char str containing new value
 * @brief makes all components for new node and adds to env linked list
 * @todo check return / need exit code?
*/
void	make_node(t_parser *node, t_env **env, char *n_k, char *n_v)
{
	int		h_v;
	t_env	*new_node;
	char	*new_full;

	h_v = 0;
	h_v = get_key_value(node->proc->str, &n_k, &n_v);
	new_full = ft_strdup(node->proc->str);
	if (new_full == NULL)
		return ;
	new_node = env_lstnew(n_k, n_v, new_full, h_v);
	env_lstadd_back(env, new_node);
}
