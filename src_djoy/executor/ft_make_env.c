/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_make_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:46:46 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/15 18:26:15 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param key data passed from environment before = sign
 * @param value data passed from environment after = sign
 * @brief malloc's and init node for linked list containing: 
 * key, value and next
 * @return node made
 * @todo 
 * 1) needs to add previous in case of doubly linked list
*/
t_env	*env_lstnew(void *key, void *value, char *full)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->full = full;
	new->path = NULL;
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
void	get_key_value(char *str, char **key, char **value)
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

char	*get_full(char *str)
{
	char	*new_str;

	new_str = NULL;
	if (str)
		new_str = ft_substr(str, 0, ft_strlen(str));
	return (new_str);
}

/**
 * @param lst linked list to loop through
 * @brief loops to list to go to last position
*/
t_env	*env_lstlast(t_env *lst)
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
void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (*lst)
	{
		last = env_lstlast(*lst);
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
t_env	*env_list(char **envp)
{
	int		i;
	char	*key;
	char	*value;
	char	*full;
	t_env	*env;

	i = 0;
	env = NULL;
	if (envp[i] == NULL)
		mini_error("env", errno);
	while (envp[i] != NULL)
	{
		get_key_value(envp[i], &key, &value);
		full = get_full(envp[i]);
		env_lstadd_back(&env, env_lstnew(key, value, full));
		i++;
	}
	return (env);
}

char	**list_to_string(t_env *env)
{
	char	**env_array;
	int		i;

	i = 0;
	// env_array = (char **)malloc(sizeof(mini_lstsize(env) + 1));
	env_array = (char **)malloc((mini_lstsize(env) + 1) * sizeof(char *));
	if (!env_array)
		mini_error ("malloc", errno);//or need to return NULL?
	while (env)
	{
		env_array[i] = env->full;
		i++;
		env = env->next;
	}
	env_array[i] = NULL;
	return(env_array);
}

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key or value
*/
void	print_list(t_env *env)
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
void	print_list_key(t_env *env)
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
void	print_list_value(t_env *env)
{
	while (env != NULL)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
}

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key or value
*/
void	print_env_list(t_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
		printf("iterations [%d]\n", i);
	}
}

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env full
*/
void	print_list_full(t_env *env)
{
	while (env != NULL)
	{
		printf("%s\n", env->full);
		env = env->next;
	}
}
