/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 18:12:37 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/09 18:20:05 by dreijans      ########   odam.nl         */
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
	printf("what the shell env\n");
	while (head != NULL)
	{
		if (head->has_value)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	// printf("---------------------------------------------------");
	// print_list_full(env);
}
