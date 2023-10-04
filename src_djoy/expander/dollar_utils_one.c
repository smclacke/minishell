/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_utils_one.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 14:05:34 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/04 14:39:00 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param node node from parser linked list
 * @param env environment linked list 
 * @param exp expander struct
 * @param len lenght of node->str
 * @brief checks if $ present and needs expanding
*/
void	dollar(t_parser *node, t_env **env, t_expand *exp, int len)
{
	if (ft_strnstr(node->str, "$", len))
	{
		exp = malloc(sizeof (t_expand));
		init_expand_struct(exp);
		exp_dollar(node, env, exp, len);
	}
}

/**
 * @param node node from parser linked list
 * @param exp expander struct
 * @param i index
 * @param len lenght of node->str
 * @brief checks if $ is at the end of the string
 * @return 1 if the $ is at the end of the string
 * 0 if not.
*/
int	check_at_len(t_parser *node, t_expand *exp, int i, int len)
{
	if (node->str[i] == '$' && (i + 1) == len)
	{
		free_remain_struct(exp);
		return (1);
	}
	return (0);
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
 * @param node parser linked list
 * @param env environmet linked list
 * @brief checks for a $ sign in the node
 * expands the string to actual value
 * @todo when "" '' quotes are handled check and adjust again
*/
void	exp_dollar(t_parser *node, t_env **env, t_expand *exp, int len)
{
	int			i;
	int			j;

	i = 0;
	while (node->str[i] != '\0')
	{
		if (check_at_len(node, exp, i, len) != 0)
			return ;
		else if (node->str[i] == '$' && (i + 1) != len)
		{
			get_before_dollar(node, exp, i);
			i++;
			j = i;
			get_compare_str(node, exp, i, j);
			if (get_check_value(exp, env) != 0)
				break ;
			free(exp->comp_str);
			reassing_before_dollar(exp);
			i = j - 1;
		}
		i++;
	}
	return_exp(node, exp);
}
