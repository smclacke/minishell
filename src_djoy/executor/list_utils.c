/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 14:48:44 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/17 14:52:51 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

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

int	mini_lstsize(t_env *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
