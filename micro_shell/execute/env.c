/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:22:10 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/26 15:36:37 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param key data passed from environment before = sign
 * @param value data passed from environment after = sign
 * @brief malloc's and init node for linked list containing: 
 * key, value and next
 * @return node made
 * @todo 
 * 1) needs to add previous in case of doubly linked list
*/
t_env	*micro_env_lstnew(void *key, void *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
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
void	micro_get_key_value(char *str, char **key, char **value)
{
	int		i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '=')
	{
		*key = ft_substr(str, 0, i);
		*value = ft_substr(str, i + 1, (ft_strlen(str) - i));
	}
}

/**
 * @param lst linked list to loop through
 * @brief loops to list to go to last position
*/
t_env	*micro_env_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/**
 * @param lst linked list
 * @param new new node to be added to linked list 
 * @brief loops through list to add the new node to the back
 * @todo adding previous in case of doubly linked list
*/
void	micro_env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (*lst)
	{
		last = micro_env_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

/**
 * @param i integer to iterate through environmental pointer
 * @param key char string to be receiving value of env key
 * @param value char string to be receiving value of env value
 * @param env linked list containing key and env
 * @brief putting the envp content into a linked list seperated by key and value
 * @return linked list 
*/
t_env	*micro_env_list(char **envp)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*env;

	i = 0;
	env = NULL;
	if (envp[i] == NULL)
		micro_error("env", errno);
	while (envp[i] != NULL)
	{
		micro_get_key_value(envp[i], &key, &value);
		micro_env_lstadd_back(&env, micro_env_lstnew(key, value));
		i++;
	}
	return (env);
}

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key or value
*/
void	micro_print_list(t_env *env)
{
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key or value
*/
void	micro_print_list_key(t_env *env)
{
	while (env != NULL)
	{
		printf("%s\n", env->key);
		env = env->next;
	}
}

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key or value
*/
void	micro_print_list_value(t_env *env)
{
	while (env != NULL)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
}
