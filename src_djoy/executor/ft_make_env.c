/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_make_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:46:46 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/13 22:35:03 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param key data passed from environment before = sign
 * @param value data passed from environment after = sign
 * @brief malloc's and init node for linked list containing: 
 * key, value and next
 * @return node made
*/
t_env	*env_lstnew(void *key, void *value, char *full, int has_value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->full = full;
	new->next = NULL;
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
		*key = ft_substr(str, 0, i);
		*value = ft_substr(str, i + 1, (ft_strlen(str) - i));
		has_value = TRUE;
	}
	else
	{
		*key = ft_substr(str, 0, i);
		has_value = FALSE;
	}
	return (has_value);
}

/**
 * @param str string from 2d array
 * containing line from envp.
 * @brief substrings string from envp[i].
*/
char	*get_full(char *str)
{
	char	*new_str;

	new_str = NULL;
	if (str)
		new_str = ft_substr(str, 0, ft_strlen(str));
	return (new_str);
}

/**
 * @param i integer to iterate through environmental pointer
 * @param key char string to be receiving value of env key
 * @param value char string to be receiving value of env value
 * @param env linked list containing key and env
 * @brief putting the envp content into a linked list seperated by key and value
 * @return linked list
 * @todo do i want to keep full??
*/
t_env	*env_list(char **envp, t_env *env)
{
	int		i;
	int		has_value;
	char	*key;
	char	*value;
	char	*full;

	i = 0;
	if (envp[i] == NULL)
		mini_error("env", errno);
	while (envp[i] != NULL)
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
	env_array = (char **)malloc((mini_lstsize(env) + 1) * sizeof(char *));
	if (!env_array)
		mini_error ("malloc", errno);
	while (env)
	{
		env_array[i] = env->full;
		i++;
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
