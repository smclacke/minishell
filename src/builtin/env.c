/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:16:24 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/31 18:35:28 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key and value
*/
void	ft_env(t_env *env)
{
	t_env	*head;

	head = env;
	while (head != NULL)
	{
		if (head->has_value)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}
