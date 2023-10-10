/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_utils_two.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 12:19:48 by dreijans      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/10/10 20:01:27 by dreijans      ########   odam.nl         */
=======
/*   Updated: 2023/10/10 18:52:11 by smclacke      ########   odam.nl         */
>>>>>>> sarah
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param exp expander struct
 * @brief reassigns exp->before_dollar with expanded value
 * free the string containing the value and temp string used
 * for swapping
*/
void	reassing_before_dollar(t_expand *exp)
{
	char	*temp;

	temp = NULL;
	temp = exp->before_dollar;
	exp->before_dollar = ft_strjoin(exp->before_dollar, exp->env_value);
	free(temp);
}

/**
 * @param env expander struct
 * @param exp environmet linked list
 * @brief checks environment value of string to be expanded
 * if there is no value it free's the comp_str and env_value.
 * @return 1 if there is no value, 0 if value is found and assigned
*/
int	get_check_value(t_expand *exp, t_env **env)
{
	char	*temp;
	t_env	*head;

	temp = NULL;
	head = *env;
	while (head)
	{
		if (mini_strcmp(exp->comp_str, head->key) == 0)
		{
			temp = exp->env_value;
			exp->env_value = ft_substr(head->value, 0, ft_strlen(head->value));
			free(temp);
			break ;
		}
		head = head->next;
	}
	if (exp->env_value == NULL)
	{
		// free(exp->comp_str);
		free_strs(exp->comp_str, exp->env_value);
		exp->comp_str = NULL;
		exp->env_value = NULL;
		return (1);
	}
	return (0);
}

/**
 * @param node node from parser linked list
 * @param exp expander struct
 * @brief replaces the node->str with expanded value and frees
 * temp, before_dollar and the entire expand struct.
*/
char	*return_exp(char *str, t_expand *exp)
{
	char	*temp;
	int		len;

	temp = str;
	len = ft_strlen(exp->before_dollar);
	str = ft_substr(exp->before_dollar, 0, len);
	free_strs(temp, exp->before_dollar);
	free(exp->env_value);
	free(exp);
	temp = NULL;
	ft_bzero(exp, sizeof(exp));
	return (str);
}

/**
 * @param exp expander struct
 * @brief free comp-str
 * calls reassing_before_dollar that set's value to before_dollar
*/
void	save_expanded(t_expand *exp)
{
	if (exp->env_value != NULL)
	{
		free(exp->comp_str);
		reassing_before_dollar(exp);
	}
}
