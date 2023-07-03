/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 13:29:40 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/03 11:08:14 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/* makes a new node from content passed to this function */
t_env	*mini_lstnew(void *content)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
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

/* adds new node to the back */
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

/* error message with perror */
void	mini_error(char *string, int error)
{
	perror(string);
	exit(error);
}

/* function that puts env in a linked list */
void	env_list(char **envp, t_env **env)
{
	int		i;
	t_env	*new;

	i = 0;
	if (envp == NULL)
		mini_error("env", errno);
	while (envp[i] != NULL)
	{
		new = mini_lstnew(envp[i]);
		mini_lstadd_back(env, new);
		i++;
	}
}

// void	print_list(t_env *env)
// {
// 	while (env != NULL)
// 	{
// 		printf("%s\n", env->content);
// 		env = env->next;
// 	}
// }
