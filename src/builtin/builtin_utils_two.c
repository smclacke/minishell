/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils_two.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:27:49 by dreijans      #+#    #+#                 */
/*   Updated: 2023/11/29 14:08:14 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

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
