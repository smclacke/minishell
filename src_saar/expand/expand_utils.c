/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 16:59:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/24 17:23:39 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/shelly.h"

// /**
//  * @param env expander struct
//  * @param exp environmet linked list
//  * @brief checks environment value of string to be expanded
//  * if there is no value it free's the comp_str and env_value.
//  * @return 1 if there is no value, 0 if value is found and assigned
// */
int	get_check_value(t_exp_dol *str, t_env **env)
{
	char	*temp;
	t_env	*head;

	temp = NULL;
	head = *env;
	while (head)
	{
		if (mini_strcmp(str->expand_this, head->key) == 0)
		{
			temp = str->env_val;
			str->env_val = ft_substr(head->value, 0, ft_strlen(head->value));
			str->assed = ft_strjoin(str->assed, str->env_val);
			printf("str->assed = %s\n", str->assed);
			free(temp);
			break ;
		}
		head = head->next;
	}
	if (!str->env_val)
	{
		free(str->expand_this);
		free(str->env_val);
		// free_strs(str->expand_this, str->env_val);
		str->expand_this = NULL;
		str->env_val = NULL;
		return (1);
	}
	return (0);
}
