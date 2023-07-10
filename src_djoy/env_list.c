/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 13:29:40 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/10 20:30:26 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/* makes a new node from content passed to this function */
t_env	*mini_lstnew(void *key, void *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

// index of = , before is key after is value, substring it
void	get_key_value(char *str, char **key, char **value)
{
	int		i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '=')
	{
		*key = ft_substr(str, 0, (i - 1));// without '='
		*value = ft_substr(str, i + 1, (ft_strlen(str) - i));
	}
}

/* loops to list to go to last position */
t_env	*mini_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/* adds new node to the back 
 if the lst has no nodes, sets new node as the start of lst
 */
void	mini_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (*lst)
	{
		last = mini_lstlast(*lst);
		last->next = new;
		//if using previous change it here too
	}
	else
		*lst = new;
}

/* function that puts env in a linked list */
t_env	*env_list(char **envp)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*env;

	i = 0;
	env = NULL;
	if (envp[i] == NULL)
		mini_error("env", errno);
	while (envp[i] != NULL)
	{
		get_key_value(envp[i], &key, &value);
		mini_lstadd_back(&env, mini_lstnew(key, value));
		i++;
	}
	return (env);
}
