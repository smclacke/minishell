/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 12:19:48 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/04 13:29:36 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param node node from parser linked list
 * @param exp expander struct
 * @param i index
 * @param j index at next $ sign
 * @brief gets the string to compare the environment key to
*/
void	get_compare_str(t_parser *node, t_expand *exp, int i, int j)
{
	while (node->str[j] != '$' && node->str[j] != '\0')
		j++;
	exp->comp_str = ft_substr(node->str, i, j - i);
}

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
	free_strs(temp, exp->env_value);
}

/**
 * @param node node from parser linked list
 * @param exp expander struct
 * @brief replaces the node->str with expanded value and frees
 * temp, before_dollar and the entire expand struct.
*/
void	return_exp(t_parser *node, t_expand *exp)
{
	char	*temp;
	int		len;

	temp = node->str;
	len = ft_strlen(exp->before_dollar);
	node->str = ft_substr(exp->before_dollar, 0, len);
	free_strs(temp, exp->before_dollar);
	free(exp);
}

/**
 * @param node node from parser linked list
 * @param exp expander struct
 * @param i index
 * @brief replaces the before_dollar string if it's NULL with 
 * node->str content of i lenght.
*/
void	get_before_dollar(t_parser *node, t_expand *exp, int i)
{
	if (exp->before_dollar == NULL)
		exp->before_dollar = ft_substr(node->str, 0, i);
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
			exp->env_value = ft_substr(head->value, 0, ft_strlen(head->value));
		head = head->next;
	}
	if (exp->env_value == NULL)
	{
		free_strs(exp->comp_str, exp->env_value);
		return (1);
	}
	return (0);
}
