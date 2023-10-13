/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 14:05:34 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/14 00:10:58 by smclacke      ########   odam.nl         */
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
static int	get_var_str(char *str, t_expand *exp, int i, int j)
{
	while (ft_isquote(str[i]) && str[i] != '\0')
		i++;
	j = i;
	while (!ft_isquote(str[j]) && str[j] != '\0')
		j++;
	exp->var = ft_substr(str, i, j - i);
	return (j);
}

static char	*exp_dollar(char *str, t_env **env, t_expand *exp, int len)
{
	int			i;
	int			j;

	i = 0;
	printf("str = %s\n", str);
	while (str[i])
	{
		if (((str[i] == '$') || (ft_isquote(str[i]))) && (i + 1) != len)
		{
			get_before_dollar(str, exp, i);
			if (ft_isquote(str[i]) && (i + 1) != len)
			{
				i = get_var_str(str, exp, i, j);
				exp->var = remove_quotes(exp->var);
				reassing_before_dollar_with_var(exp);
			}
			else
			{		
				i++;
				j = i;
				if (i == len)
				{
					str = return_exp(str, exp);
					return (str);
				}
				get_compare_str(str, exp, i, j);
				get_check_value(exp, env);
				save_expanded(exp);
			}
		}
		i++;
	}
	printf("str before ret = %s\n", str);
	str = return_exp(str, exp);
	printf("str ret = %s\n", str);
	return (str);
}

/**
 * @param node node from parser linked list
 * @param env environment linked list 
 * @param exp expander struct
 * @param len lenght of node->str
 * @brief checks if $ present and needs expanding
*/
char	*dollar(char *str, t_env **env, t_expand *exp, int len)
{
	char	*exp_str;
	int		i;

	exp_str = NULL;
	i = 0;
	if (ft_strnstr(str, "$", len))
	{
		exp_str = check_if_expand(str);
		if (!exp_str)
		{
			str = remove_quotes(str);
			return (str);
		}
		exp = ft_calloc(1, sizeof (t_expand));
		while (exp_str[i])
		{
			if (check_at_len(exp_str, exp, i, len))
				return (exp_str);
			i++;
		}
		exp_str = exp_dollar(exp_str, env, exp, len);
	}
	return (exp_str);
}
