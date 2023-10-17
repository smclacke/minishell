/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 14:48:44 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/17 18:18:04 by dreijans      ########   odam.nl         */
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

/**
 * @param lst linked list
 * @brief loops through list count length
 * @return int size
*/
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

//acting suspicious
void	free_env(t_env **lst)
{
	t_env	*temp;

	while (*lst && lst)
	{
		temp = (*lst)->next;
		free((*lst)->key);
		free((*lst)->value);
		free((*lst)->full);
		(*lst) = temp;
		// free(temp);
	}
	free (*lst);
	// *lst = NULL;
}

void	free_data(t_execute *data)
{
	data->fd_in = 0;
	data->fork_pid = 0;
	data->pipe_fd_1[READ] = 0;
	data->pipe_fd_1[WRITE] = 0;
	data->pipe_fd_2[READ] = 0;
	data->pipe_fd_2[WRITE] = 0;
	free(data->path);
	data->in = 0;
	data->out = 0;
	// if (data->env_array != NULL)
	// {
	ft_free_arr(data->env_array);
	// 	printf("just hanging arounfd\n");
	// 	data->env_array = NULL;
	// }
	free (data);
}
