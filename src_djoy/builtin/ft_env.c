/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 18:12:37 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/21 15:43:51 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key and value
 * @todo doesnt give update version after cd etc need to do that??
 * whyyyyyy??????
 * why overschrijven hoeezooo???
*/
void	ft_env(t_env *env)
{
	t_env	*head;

	head = env;
	printf("what the shell env\n");
	while (head != NULL)
	{
		printf("%s=%s\n", head->key, head->value);
		// printf("%s\n", head->key);
		// printf("%s\n", head->value);
		// printf("%s\n", head->full);
		head = head->next;
	}
}
