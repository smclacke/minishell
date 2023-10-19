/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 14:42:33 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/19 22:06:06 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param node pointer to node in list given in the form of a string
 * @param env pointer to linked list
 * @brief export with no options
 * @todo check if varaible already exists, overwrite it.
*/
void	micro_ft_export(t_parser *node, t_env *env)
{
	int		i;
	char	*new_key;
	char	*new_value;
	t_env	*new_node;

	i = 0;
	if (ft_strchr(node->str, '=') == 0)
		micro_error("strchr", errno);
	micro_get_key_value(node->str, &new_key, &new_value);
	new_node = micro_env_lstnew(new_key, new_value);
	micro_env_lstadd_back(&env, new_node);
}

//first character cannot have a number but everything else can have
//check export edge cases