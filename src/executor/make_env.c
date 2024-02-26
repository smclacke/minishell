/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:15:00 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/26 14:03:06 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param key data passed from environment before = sign
 * @param value data passed from environment after = sign
 * @brief malloc's and init node for linked list containing: 
 * key, value and next
 * @return node made
 * @note make sure to bzero same amount as malloc, or use calloc
*/
t_env	*env_lstnew(void *key, void *value, char *full, int has_value)
{
	t_env	*new;

	new = (t_env *)mini_malloc(sizeof(t_env));
	ft_bzero(new, sizeof(t_env));
	new->key = key;
	new->value = value;
	new->full = full;
	new->has_value = has_value;
	return (new);
}

/**
 * @param str string to be divided by = sign
 * @param key pointer to the address of a pointer 
 * containing a string substringed from str before = sign
 * @param value pointer to the address of a pointer 
 * containing a string substringed from str after = sign
 * @brief substrings key and value from str without the '=' sign
*/
int	get_key_value(char *str, char **key, char **value)
{
	int		i;
	int		has_value;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '=')
	{
		if (ft_strlen(str) == 1)
		{
			*key = str;
			value = NULL;
			return (has_value = FALSE);
		}
		*key = mini_substr(str, 0, i);
		*value = mini_substr(str, i + 1, (ft_strlen(str) - i));
		has_value = TRUE;
	}
	else
	{
		*key = mini_substr(str, 0, i);
		*value = NULL;
		has_value = FALSE;
	}
	return (has_value);
}

/**
 * @param str string from 2d array
 * containing line from envp.
 * @brief substrings string from envp[i].
*/
static char	*get_full(char *str)
{
	char	*new_str;

	new_str = NULL;
	if (str)
		new_str = mini_substr(str, 0, ft_strlen(str));
	return (new_str);
}

/**
 * @param i integer to iterate through environmental pointer
 * @param key char string to be receiving value of env key
 * @param value char string to be receiving value of env value
 * @param env linked list containing key and env
 * @brief putting the envp content into a linked list seperated by key and value
 * @return linked list
*/
t_env	*env_list(char **envp, t_env *env)
{
	int		i;
	int		has_value;
	char	*key;
	char	*value;
	char	*full;

	i = 0;
	key = NULL;
	value = NULL;
	full = NULL;
	if (envp[i] == NULL)
		return (0);
	while (envp && envp[i] != NULL)
	{
		has_value = get_key_value(envp[i], &key, &value);
		full = get_full(envp[i]);
		env_lstadd_back(&env, env_lstnew(key, value, full, has_value));
		i++;
	}
	return (env);
}

/**
 * @param env linked list containing environment
 * @brief turns environment linked list into 2d array
*/
char	**list_to_string(t_env *env)
{
	char	**env_array;
	int		i;

	i = 0;
	env_array = (char **)mini_malloc((mini_lstsize(env) + 1) * sizeof(char *));
	while (env)
	{
		env_array[i] = env->full;
		i++;
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
