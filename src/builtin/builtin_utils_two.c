/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils_two.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:27:49 by dreijans      #+#    #+#                 */
/*   Updated: 2023/11/29 17:08:52 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

#define ARG_ERROR "minishell: %s: too many arguments\n"

/**
 * @param temp temporary placeholder
 * @param str old working directory string
 * @param env environment in linked list
 * @brief replaces the value of set key in the environment
*/
void	reasing_value(char *str, t_env *env)
{
	char	*temp;

	temp = NULL;
	temp = env->value;
	env->value = str;
	free(temp);
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
bool	check_args(t_parser *lst)
{
	int			i;

	i = list_iter(lst);
	if (i > 2)
	{
		lst = lst->next;
		if (lst->meta)
			return (true);
		dprintf(STDERR_FILENO, ARG_ERROR, lst->cmd);
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
 * @todo check return here
*/
void	make_node(t_parser *node, t_env **env, char *n_k, char *n_v)
{
	int		h_v;
	t_env	*new_node;
	char	*new_full;

	h_v = 0;
	h_v = get_key_value(node->str, &n_k, &n_v);
	new_full = ft_strdup(node->str);
	if (new_full == NULL)
		return ;//really?? error message 
	new_node = env_lstnew(n_k, n_v, new_full, h_v);
	env_lstadd_back(env, new_node);
}
