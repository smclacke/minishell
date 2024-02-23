/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:16:24 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/23 21:17:44 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key and value
*/
void	ft_env(t_env *env, t_parser *lst)
{
	t_env		*head;

	head = env;
	if (lst->proc->str_count != 0)
	{
		ft_putstr_fd(NOT_POSSIBLE, STDERR_FILENO);
		lst->exit_code = E_COMMAND_NOT_FOUND;
		return ;
	}
	while (head != NULL)
	{
		if (head->has_value)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}
