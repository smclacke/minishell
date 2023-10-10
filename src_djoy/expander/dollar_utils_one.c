/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_utils_one.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 14:05:34 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/10 20:01:19 by dreijans      ########   odam.nl         */
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
char	*dollar(char *str, t_env **env, t_expand *exp, int len)
{
	if (ft_strnstr(str, "$", len))
	{
		exp = ft_calloc(1, sizeof (t_expand));
		str = exp_dollar(str, env, exp, len);
	}
	return (str);
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
int	check_at_len(char *str, t_expand *exp, int i, int len)
{
	if (str[i] == '$' && (i + 1) == len)
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
void	get_before_dollar(char *str, t_expand *exp, int i)
{
	if (exp->before_dollar == NULL)
		exp->before_dollar = ft_substr(str, 0, i);
}

/**
 * @param node node from parser linked list
 * @param exp expander struct
 * @param i index
 * @param j index at next $ sign
 * @brief gets the string to compare the environment key to
*/
void	get_compare_str(char *str, t_expand *exp, int i, int j)
{
	while (str[j] != '$' && str[j] != '\0')
		j++;
	exp->comp_str = ft_substr(str, i, j - i);
}

/**
 * @param node parser linked list
 * @param env environmet linked list
 * @brief checks for a $ sign in the node
 * expands the string to actual value
 * @todo when "" '' quotes are handled check and adjust again
*/
char	*exp_dollar(char *str, t_env **env, t_expand *exp, int len)
{
	int			i;
	int			j;

	i = 0;
	while (str[i] != '\0')
	{
		if (check_at_len(str, exp, i, len) != 0)
			return (str);
		else if (str[i] == '$' && (i + 1) != len)
		{
			get_before_dollar(str, exp, i);
			i++;
			j = i;
			get_compare_str(str, exp, i, j);
			get_check_value(exp, env);
			save_expanded(exp);
			i = j - 1;
		}
		i++;
	}
	str = return_exp(str, exp);
	return (str);
}
