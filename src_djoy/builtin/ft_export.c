/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 14:42:33 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/18 12:41:43 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param argv argument given in the form of a string
 * @param env pointer to linked list
 * @brief export with no options
 * @todo check if varaible already exists, overwrite it.
*/
void	ft_export(char **argv, t_env *env)
{
	int		i;
	char	*new_key;
	char	*new_value;
	t_env	*new_node;

	i = 0;
	if (ft_strchr(argv[2], '=') == 0)
		mini_error("strchr", errno);
	get_key_value(argv[2], &new_key, &new_value);
	new_node = mini_lstnew(new_key, new_value);
	mini_lstadd_back(&env, new_node);
}
