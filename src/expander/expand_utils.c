/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 16:59:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/03 22:25:43 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/shelly.h"

/**
 * @param env expander struct
 * @param exp environmet linked list
 * @brief checks environment value of string to be expanded
 * if there is no value it free's the comp_str and env_value.
 * @return 1 if there is no value, 0 if value is found and assigned
 * @todo triple check protection, norm and sooo when less tired
*/
int	get_check_value(t_expand *str, t_env **env)
{
	t_env	*head;

	head = *env;
	while (head)
	{
		if (mini_strcmp(str->dollar, head->key) == 0)
		{
			str->env_val = ft_substr(head->value, 0, ft_strlen(head->value));
			str->dollar = str->env_val;
			return (0);
		}
		head = head->next;
	}
	return (1);
}
